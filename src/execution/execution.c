/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 15:52:55 by emartine          #+#    #+#             */
/*   Updated: 2019/04/09 13:42:41 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"
#include "execution.h"
#include "expansions.h"

static char	**arg_to_argv(t_lexer_token *cmd)
{
	size_t	i;
	t_argv	*cur;
	char	**av;

	if (NULL == (av = malloc((cmd->argc + 1) * sizeof(*av))))
		return (NULL);
	i = 0;
	cur = cmd->argv_head;
	while (i < cmd->argc)
	{
		av[i] = cur->buffer;
		i++;
		cur = cur->next;
	}
	av[cmd->argc] = NULL;
	return (av);
}

static void	manage_job(void)
{
	t_job	*tmp;

	launch_job(g_shell.head_job, 1);
	tmp = g_shell.head_job;
	while (tmp)
	{
		if (job_is_stop(tmp) == 0)
		{
			free_job(g_shell.head_job);
			g_shell.head_job = NULL;
		}
		tmp = tmp->next;
	}
}

void		execution(t_lexer *lex)
{
	char	**av;

	if (lex->root == NULL)
		return ;
	if (lex->root->ptype != PARSER_COMMAND || !lex->root->arg_head)
		return ;
	if (do_expansions(lex) < 0)
		return ;
	if ((av = arg_to_argv(lex->root->arg_head)))
	{
		if (command_redir(lex->root) < 0)
		{
			// TODO $?
			return ;
		}
		g_shell.head_job = add_job(g_shell.head_job, creat_job_list(av));
		manage_job();
		command_redir_restore(lex->root);
		resize_history(g_shell.hist.history);
	}
}
