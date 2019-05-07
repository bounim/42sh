/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:38:54 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/10 18:56:26 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"
#include "execution.h"
#include "lexer/lexer_internal.h"

t_job			*create_job(t_lexer_token *cmd)
{
	t_job	*new;

	if (!(new = init_job()))
		return (NULL);
	if (cmd)
		new->cmd = lst_to_str(cmd, 0);
	return (new);
}

t_job			*create_job_argv(char **argv)
{
	t_job	*new;
	char	*cmd;

	if (!(cmd = ft_arrjoin(argv)))
		return (NULL);
	if (!(new = create_job(NULL)))
	{
		free(cmd);
		return (NULL);
	}
	new->cmd = cmd;
	return (new);
}

t_proc			*add_proc_list(t_job *job, t_proc *new)
{
	new->job = job;
	if (job->foot_proc)
	{
		new->prev = job->foot_proc;
		job->foot_proc->next = new;
	}
	else
		job->head_proc = new;
	job->foot_proc = new;
	return (new);
}

t_proc			*create_proc(t_job **job, t_lexer_token *cmd)
{
	t_proc	*new;

	if (!*job && !(*job = create_job(cmd)))
		return (NULL);
	if (!(new = init_proc()))
		return (NULL);
	new->arg = arg_to_argv(cmd);
	new->cmd = cmd;
	new->envl = dup_envl(g_shell.envl);
	if (execute_assign_list(cmd, new) < 0)
		new->error = 125;
	else if (new->arg && !(new->is_builtin = check_builtin(new->arg[0])))
	{
		if ((new->find_error = find_command(new->path,
						new->arg[0], new->envl)) != 0)
			new->error = 127;
	}
	return (add_proc_list(*job, new));
}
