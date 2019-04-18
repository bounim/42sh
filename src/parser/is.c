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

uint8_t					is_sep_operator(t_lexer_token *t)
{
	return (t && t->type == LEX_TP_OP
			&& !(t->buffer[0] == '<' || t->buffer[0] == '>'));
}

enum e_parser_type		get_node_type(t_lexer_token *token)
{
	if (token->type == LEX_TP_OP)
	{
		if (token->size == 1)
		{
			if (token->buffer[0] == '&' || token->buffer[0] == ';')
				return (PARSER_SEPARATOR);
			if (token->buffer[0] == '|')
				return (PARSER_PIPE);
		}
		else if (token->size == 2
				&& (token->buffer[0] == '|' || token->buffer[0] == '&')
				&& token->buffer[0] == token->buffer[1])
			return (PARSER_AND_OR);
	}
	return (PARSER_COMMAND);
}

enum e_redirect_type	get_redirect(uint8_t *buffer, size_t size)
{
	if (size == 3)
		return (DLESSDASH);
	if (size == 2)
	{
		if (buffer[0] == '<')
		{
			if (buffer[1] == '>')
				return (LESSGREAT);
			if (buffer[1] == '&')
				return (LESSAND);
			return (DLESS);
		}
		if (buffer[1] == '&')
			return (GREATAND);
		return (DGREAT);
	}
	if (buffer[0] == '>')
		return (GREAT);
	return (LESS);
}

size_t					is_assignment(uint8_t *buffer, size_t size)
{
	size_t	i;

	if (size == 0 || (buffer[0] >= '0' && buffer[0] <= '9'))
		return (0);
	i = 0;
	while (i < size)
	{
		if (i > 0 && buffer[i] == '=')
			return (i);
		if (!(buffer[i] == '_'
					|| (buffer[i] >= '0' && buffer[i] <= '9')
					|| (buffer[i] >= 'A' && buffer[i] <= 'Z')
					|| (buffer[i] >= 'a' && buffer[i] <= 'z')))
			return (0);
		i++;
	}
	return (0);
}
