/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 18:10:56 by kberisha          #+#    #+#             */
/*   Updated: 2019/02/07 18:10:58 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

void	parser_init(t_parser *parser)
{
	ft_memset(parser, 0, sizeof(*parser));
	parser->head = NULL;
}

void	create_tab_argument(t_lexer_token **head)
{
	t_lexer_token	*cur;
	t_lexer_token	*prev;

	cur = (*head)->next;
	while (cur && cur->type == LEX_TP_WD)
	{
		ft_memcpy((*head)->args[(*head)->args_nb], cur->buffer, cur->size);
		(*head)->args_nb++;
		prev = cur;
		cur = cur->next;
		lexer_free_token(prev);
	}
	if (cur && cur->type != LEX_TP_WD)
		(*head)->next = cur;
	else
		(*head)->next = NULL;
	
}

void	parser_light_list(t_lexer *lexer)
{
	t_lexer_token	*prev;
	t_lexer_token	*cur;

	prev = NULL;
	cur = lexer->head;
	while (cur)
	{
		if (cur->type == LEX_TP_WD)
			create_tab_argument(&cur);
		cur = cur->next;
	}
}

int		parser_create_tree(t_lexer *lexer)
{
	t_parser		*parser;
	t_lexer_token	*tmp;
	t_parser_node	*n;

	// size_t i = 0;
	n = NULL;
	if (!(parser = malloc(sizeof(*parser))))
		return (-1);
	parser_init(parser);
	parser_light_list(lexer);
	tmp = lexer->head;
	while (tmp)
	{
		if (!(n = parser_new_elem(tmp)))
			return (-1);
		ft_putstr("currently on ");
		print_token(n->buffer, n->buffer_length);
		// if (n->args_nb)
		// {
			// while (i < n->args_nb)
		printf("new->type == %d\n", n->type);
		parser_add_tree(&parser->head, n);
		tmp = tmp->next;
	}
	structure(parser->head, 0);
	// parser_print(parser->head);
	return (0);
}
