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

void	parser_init(t_parser *parser)
{
	ft_memset(parser, 0, sizeof(*parser));
	parser->head = NULL;
}

int		parser_node(uint8_t *buf, size_t size, enum e_lexer_type type)
{
	t_parser_node	*n;

	if (!(n = malloc(sizeof(*n))))
		return (-1);
	ft_memset(n, 0, sizeof(*n));
	ft_memcpy(n->buffer, buf, size);

}
