/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 01:32:18 by kberisha          #+#    #+#             */
/*   Updated: 2019/02/18 01:32:20 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

/*int		parser_add_node(t_parser *parser, t_parser_node *n)
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

t_parser_node	*parser_node(uint8_t *buf, size_t size, enum e_parser_type)

	t_parser_node	*n;

	if (!(n = malloc(sizeof(*n))))
		return (NULL);
	ft_memset(n, 0, sizeof(*n));
	ft_memcpy(n->buffer, buf, size);
	n->cmd_type = type;
	return (n);
}
*/
