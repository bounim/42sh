/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 15:52:55 by emartine          #+#    #+#             */
/*   Updated: 2019/04/15 15:05:52 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"
#include "execution.h"
#include "expansions.h"

static char	**arg_to_argv(t_lexer_token *cmd)
{
	size_t			i;
	t_lexer_token	*cur;
	char			**av;

	if (NULL == (av = malloc((cmd->arg_nb + 1) * sizeof(*av))))
		return (NULL);
	i = 0;
	cur = cmd->arg_head;
	while (i < cmd->arg_nb)
	{
		av[i] = (char *)cur->buffer;
		i++;
		cur = cur->arg_next;
	}
	av[cmd->arg_nb] = NULL;
	return (av);
}

void		execution(t_lexer *lex)
{
	char	**av;
	t_job	*new;

	if (lex->root == NULL)
		return ;
	if (lex->root->ptype != PARSER_COMMAND || !lex->root->arg_head)
		return ;
	if (command_expansions(lex->root) < 0)
		return ;
	if ((av = arg_to_argv(lex->root->arg_head)))
	{
		if (command_redir(lex->root) < 0)
		{
			// TODO $?
			return ;
		}
		new = creat_job_list(av);
		g_shell.head_job = add_job(g_shell.head_job, new);
		launch_job(new, 1);
		job_notif();
		command_redir_restore(lex->root);
		resize_history(g_shell.hist.history);
	}
}
