/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 15:52:55 by emartine          #+#    #+#             */
/*   Updated: 2019/03/21 15:52:57 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"
#include "execution.h"

/*static char	**arg_to_argv(t_word *head)
{
	size_t	ac;
	t_word	*cur;
	size_t	i;
	char	**av;

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
		if (NULL == (av[i] = malloc(cur->buffer->size + 1)))
		{
			while (i > 0)
			{
				free(av[i - 1]);
				i--;
			}
			return (NULL);
		}
		ft_memcpy(av[i], cur->buffer->buf, cur->buffer->size);
		av[i][cur->buffer->size] = '\0';
		i++;
		cur = cur->next;
	}
	av[i] = NULL;
	return (av);
}*/

void		test_exec(t_lexer *lex)
{
	char	**av;

	(void)av;//XXX
	if (parser_create_tree(lex) < 0)
		return ;
	/*if (lex->root == NULL)
		return ;
	if (lex->root->type != PARSER_COMMAND || !lex->root->arg_head)
	{
		parser_destroy(lex);
		return ;
	}
	if ((av = arg_to_argv(lex->root->arg_head)))
	{
		// TODO exec
		start_builtin(av, NULL);
	}
	parser_destroy(lex);*/
}
