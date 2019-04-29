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

t_job	*create_job(t_lexer_token *cmd)
{
	t_job	*new;
	t_job	*cur;

	new = NULL;
	if (!(new = init_job(new)))
		return (NULL);
	new->cmd = lst_to_str(cmd);
	if (!g_shell.head_job)
	{
		g_shell.head_job = new;
		return (new);
	}
	cur = g_shell.head_job;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	return (new);
}

t_proc	*create_proc(t_job **job, t_lexer_token *cmd)
{
	t_proc	*new;
	int		r;

	new = NULL;
	if (!*job && !(*job = create_job(cmd)))
		return (NULL);
	if (!(new = init_proc(new)))
		return (NULL);
	new->arg = arg_to_argv(cmd);
	new->cmd = cmd;
	new->job = *job;
	if (!cmd->assign_head || !cmd->arg_head)
		new->envl = g_shell.envl;
	else
		new->envl = dup_envl(g_shell.envl); // TODO free
	if (execute_assign_list(cmd, new) < 0)
		new->error = 125;
	else if (new->arg && !(new->is_builtin = check_builtin(new->arg[0])))
	{
		if ((r = find_command(new->path, new->arg[0], new->envl)) != 0)
		{
			exec_error(new->arg[0], r);
			new->error = 127;
		}
	}
	if ((*job)->foot_proc)
	{
		new->prev = (*job)->foot_proc;
		(*job)->foot_proc->next = new;
	}
	else
		(*job)->head_proc = new;
	(*job)->foot_proc = new;
	return (new);
}

