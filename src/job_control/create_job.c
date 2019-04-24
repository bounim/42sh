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

	new = NULL;
	if (!*job && !(*job = create_job(cmd)))
		return (NULL);
	if (!cmd->arg_head || !(cmd->argv = arg_to_argv(cmd)) || !(new = init_proc(new)))
		return (NULL);
	new->arg = ft_arrdup(cmd->argv);
	new->cmd = cmd; //TODO
	new->job = *job;
	if (!cmd->assign_head || !cmd->arg_head)
		new->envl = g_shell.envl;
	else
		new->envl = dup_envl(g_shell.envl);
	if (!(new->is_builtin = check_builtin(cmd->argv[0])))
	{
		if (!(new->path = command_search(cmd, new->envl)) || access(new->path, X_OK))
			exec_error(cmd->argv[0], new->path);
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

