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

void	print_token(uint8_t *buffer, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		ft_putchar(buffer[i++]);
	ft_putchar('\n');
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
		print_token(root->buffer, root->buffer_length);
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
	print_token(tree->buffer, tree->buffer_length);
	if (tree->left)
	{
		ft_putendl("printing left");
		parser_print(tree->left);
	}
}
