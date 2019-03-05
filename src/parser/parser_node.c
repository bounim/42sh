/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 01:32:18 by kberisha          #+#    #+#             */
/*   Updated: 2019/02/28 04:47:50 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

enum e_parser_type	get_node_type(t_lexer_token *token)
{
	if (is_and(token->buffer, token->size) || is_or(token->buffer, token->size))
		return (PARSER_AND_OR);
	if (is_pipeline(token->buffer, token->size))
		return (PARSER_PIPE);
	if (is_shift(token->buffer, token->size))
		return (PARSER_REDIRECT);
	if (is_semicolon(token->buffer, token->size))
		return (PARSER_SEMICOLON);
	return (PARSER_COMMAND);
}

void			parser_new_cmd(t_parser_node *n, t_lexer_token *tmp)
{
	
}

t_parser_node	*parser_new_elem(t_lexer_token *new)
{
	t_parser_node	*n;

	if (!(n = malloc(sizeof(*n))))
		return (NULL);
	ft_memset(n, 0, sizeof(*n));
	if (!(n->buffer = malloc(new->size)))
		return (NULL);
	ft_memcpy(n->buffer, new->buffer, new->size);
	n->buffer_length = new->size;
	if (!(n->token = malloc(sizeof(t_lexer_token*))))
		return (NULL);
	n->token = new;
	n->type = get_node_type(new);
	// if ((n->type = get_node_type(new)) == PARSER_COMMAND)
		// parse_new_cmd(new);
	return (n);
}
