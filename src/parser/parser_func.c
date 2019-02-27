/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 01:28:43 by kberisha          #+#    #+#             */
/*   Updated: 2019/02/18 01:28:44 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

void	parser_add_cmd(t_parser_node **head, t_parser_node *new)
{
	if (!(*head)->left/* || ((*head)->left->type == PARSER_COMMAND && (*head)->type == PARSER_COMMAND)*/)
	{
		ft_putendl("going left");
		parser_add_tree(&(*head)->left, new);
	}
	else
	{
		ft_putendl("going right");
		parser_add_tree(&(*head)->right, new);
	}
}

void	parser_add_operator(t_parser_node **head, t_parser_node *new)
{
	if ((*head)->type == PARSER_COMMAND || new->type > (*head)->type)
	{
		new->left = *head;
		*head = new;
	}
	else if (new->type <= (*head)->type)
	{
		if ((*head)->right && (*head)->right->type != PARSER_COMMAND)
			parser_add_tree(&(*head)->right, new);
		else
		{
			new->left = (*head)->right;
			(*head)->right = new;
		}
	}
}

void	parser_add_tree(t_parser_node **head, t_parser_node *new)
{
	if (!*head)
	{
		ft_putendl("adding x:");
		print_token(new->buffer, new->buffer_length);
		*head = new;
	}
	else if (new->type == PARSER_COMMAND)
	{
		ft_putendl("adding cmd:");
		print_token(new->buffer, new->buffer_length);
		parser_add_cmd(head, new);
	}
	else
	{
		ft_putendl("adding ope:");
		print_token(new->buffer, new->buffer_length);
		parser_add_operator(head, new);
	}
}

