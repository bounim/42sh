/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:24:31 by kberisha          #+#    #+#             */
/*   Updated: 2019/02/27 15:24:33 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

uint8_t		is_shift(uint8_t *buffer, size_t buffer_size)
{
	if (buffer_size > 2 || (buffer[0] != '<' && buffer[0] != '>'))
		return (0);
	if (buffer_size == 1)
    return (1);
  if (buffer[1] && buffer[1] == '&')
    return (1);
  else
    return (buffer[0] == buffer[1]);
}

uint8_t		is_semicolon(uint8_t *buffer, size_t buffer_size)
{
    if (buffer_size == 1 && buffer[0] == ';')
        return (1);
    return (0);
}

uint8_t		is_pipeline(uint8_t *buffer, size_t buffer_size)
{
    if (buffer_size == 1 && buffer[0] == '|')
        return (1);
    return (0);
}

uint8_t		is_and(uint8_t *buffer, size_t buffer_size)
{
    if (buffer_size > 2 || buffer[0] != '&')
        return (0);
    if (buffer_size == 1)
		return (1);
	return (buffer[0] == buffer[1]);
}

uint8_t		is_or(uint8_t *buffer, size_t buffer_size)
{
    if (buffer_size == 2 && buffer[0] == '|' && buffer[1] == '|')
        return (1);
    return (0);
  }
  
uint8_t			is_sep_operator(t_lexer_token *t)
{
	if (t && t->type == LEX_TP_OP && !is_shift(t->buffer, t->size))
		return (1);
	return (0);
}

uint8_t          is_quote(uint8_t c)
{
    return (c == '\'' || c == '\"' || c == '\\');
}

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