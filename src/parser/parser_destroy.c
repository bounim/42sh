/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 17:12:05 by emartine          #+#    #+#             */
/*   Updated: 2019/03/20 17:12:07 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void				free_word(t_word *head)
{
	t_word	*cur;
	t_word	*prev;

	cur = head;
	while (cur)
	{
		prev = cur;
		cur = cur->next;
		free(prev->buffer->buf);
		free(prev->buffer);
		free(prev);
	}
}

static void				free_node(t_parser_node *current)
{
	t_redir	*cur;
	t_redir	*prev;

	cur = current->redir_head;
	while (cur)
	{
		prev = cur;
		cur = cur->next;
		free(prev->buffer->buf);
		free(prev->buffer);
		free(prev);
	}
	free_word(current->assign_head);
	free_word(current->arg_head);
	free(current->buffer);
	free(current);
}

void	parser_destroy(t_parser *parser)
{
	t_parser_node	*current;
	t_parser_node	*previous;

	current = parser->nodeList;
	while (current)
	{
		previous = current;
		current = current->listNext;
		free_node(previous);
	}
}
