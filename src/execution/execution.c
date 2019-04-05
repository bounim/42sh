/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 15:52:55 by emartine          #+#    #+#             */
/*   Updated: 2019/04/05 15:24:59 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"
#include "execution.h"

static char	**arg_to_argv(t_lexer_token *head)
{
	size_t			ac;
	t_lexer_token	*cur;
	size_t			i;
	char			**av;

	ac = 0;
	cur = head;
	while (cur)
	{
		ac++;
		cur = cur->next;
	}
	if (NULL == (av = malloc(((size_t)ac + 1) * sizeof(*av))))
		return (NULL);
	cur = head;
	i = 0;
	while (cur)
	{
		if (NULL == (av[i] = malloc(cur->size + 1)))
		{
			while (i > 0)
			{
				free(av[i - 1]);
				i--;
			}
			return (NULL);
		}
		ft_memcpy(av[i], cur->buffer, cur->size);
		av[i][cur->size] = '\0';
		i++;
		cur = cur->next;
	}
	av[i] = NULL;
	return (av);
}

void		execution(t_lexer *lex)
{
	char	**av;

	if (lex->root == NULL)
		return ;
	if (lex->root->type != PARSER_COMMAND || !lex->root->arg_head)
		return ;
	if ((av = arg_to_argv(lex->root->arg_head)))
	{
		if (command_redir(lex->root) < 0)
		{
			// TODO $?
			return ;
		}
		if (!start_builtin(av, g_shell.envl))
		{
			// TODO exec
		}
		command_redir_restore(lex->root);
		resize_history(g_shell.hist.history);
	}
}
