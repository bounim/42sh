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

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	print_token(uint8_t *buffer, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		ft_putchar(buffer[i++]);
}

void	parser_print(t_parser_node *tree)
{
	if (!tree)
		return ;
	if (tree->left)
		parser_print(tree->left);
	print_token(tree->buffer, tree->buffer_length);
	if (tree->right)
		parser_print(tree->right);
}
