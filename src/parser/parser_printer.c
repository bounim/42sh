/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_printer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 01:30:55 by kberisha          #+#    #+#             */
/*   Updated: 2019/02/18 01:30:57 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "expansion.h"

void	print_token(uint8_t *buffer, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		ft_putchar(buffer[i++]);
	ft_putchar('\n');
}

void		print_word(t_word *r)
{
	t_word *tmp;

	tmp = r;
	while (tmp)
	{
		print_token(tmp->buffer->buf, tmp->buffer->size);
		tmp = tmp->next;
	}
}

void		print_redir(t_redir *r)
{
	t_redir *tmp;

	tmp = r;
	while (tmp)
	{
		print_token(tmp->buffer->buf, tmp->buffer->size);
		tmp = tmp->next;
	}
}

void	padding(char c, char n)
{
	int i;

	for (i = 0; i < n; i++)
		ft_putchar(c);
}

void	structure(t_parser_node *root, int level)
{
	if (!root)
	{
		padding('\t', level);
		puts("~");
	}
	else
	{
		structure(root->right, level + 1);
		padding('\t', level);
		if (root->type != PARSER_COMMAND)
			print_token(root->buffer, root->size);
		else if (root->arg_head)
			print_token(root->arg_head->buffer->buf, root->arg_head->buffer->size);
		structure(root->left, level + 1);
	}
}

void	parser_print(t_parser_node *tree)
{
	if (!tree)
		return ;
	if (tree->right)
	{
		ft_putendl("printing left");
		parser_print(tree->right);
	}
	print_token(tree->arg_head->buffer->buf, tree->arg_head->buffer->size);
	if (tree->left)
	{
		ft_putendl("printing left");
		parser_print(tree->left);
	}
}
