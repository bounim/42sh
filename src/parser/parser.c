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

void	parser_push_left(t_parser *parser, t_parser_node *n, int foot)
{
	t_parser_node	*tmp;

	if (foot == 1)
		tmp = parser->foot;
	else
		tmp = parser->head;
	while (tmp)
	{
		if (!tmp->left)
			break ;
		tmp = tmp->left;
	}
	tmp->left = n;
}

void	parser_push_right(t_parser *parser, t_parser_node *n)
{
	t_parser_node	*tmp;

	tmp = parser->head;
	while (tmp && tmp->type == LEX_TP_OP)
	{
		if (!tmp->right)
			break ;
		tmp = tmp->right;
	}
	tmp->right = n;
	parser->foot = n;
}

void	add_child(t_parser *parser, t_parser_node *n)
{
	if (parser->head && parser->head->type == LEX_TP_WD)
		parser_push_left(parser, n, 0);
	else
	{
		parser_push_left(parser, n, 1);
	}
}

void	add_parent(t_parser *parser, t_parser_node *n)
{
	n->left = parser->head; // ca va se supprimer si je le free apres ......
	parser->head = n;
}

int		parser_add_op(t_parser *parser, t_parser_node *n)
{
	if (parser->head->type == LEX_TP_OP)
	{
		add_end_right(parser, n);
		return (0);
	}
	else
	{
		add_parent(parser, n);
		return (parser_add_op(parser, n));
	}
}

int		parser_add_node(t_parser *parser, t_parser_node *n)
{
	if (!parser->head)
	{
		parser->head = n;
		return (0);
	}
	if (n->type == LEX_TP_OP)
		return (parser_add_op(parser, n));
	else if (n->type == LEX_TP_WD)
		return (add_child(parser, n));
	else
		ft_putendl("IO_NUMBER: what to do ?");
	return (1);
}

int		parser_node(t_parser *parser, uint8_t *buf, size_t size, enum e_lexer_type type)
{
	t_parser_node	*n;

	if (!(n = malloc(sizeof(*n))))
		return (-1);
	ft_memset(n, 0, sizeof(*n));
	ft_memcpy(n->buffer, buf, size);
	n->type = type;
	return (parser_add_node(parser, n));
}


