/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 16:23:03 by emartine          #+#    #+#             */
/*   Updated: 2019/03/30 16:23:04 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

/*
** NB: with 1>&- the - is not part of the operator but is a word of length 1
*/

int		operator_append(t_lexer *lex)
{
	uint8_t	ch;
	size_t	s;
	uint8_t	*op;

	if (lex->quoted)
		return (1);
	ch = lex->line[lex->i];
	if (lex->foot != NULL && !lex->foot->cannot_append
			&& lex->foot->type == LEX_TP_OP && ch != ';')
	{
		s = lex->foot->size;
		op = lex->foot->buffer;
		if ((ch == '|' && s == 1 && (op[0] == '|' || op[0] == '>'))
				|| (ch == '&' && s == 1 && (op[0] == '&' || op[0] == '<'
					|| op[0] == '>'))
				|| (ch == '<' && s == 1 && op[0] == '<')
				|| (ch == '>' && s == 1 && (op[0] == '>' || op[0] == '<'))
				|| (ch == '-' && s == 2 && op[0] == '<' && op[1] == '<'))
			return (append(lex));
	}
	return (1);
}

/*
** always returns 1, because it doesn't consume current character
*/

int		operator_end(t_lexer *lex)
{
	if (lex->foot != NULL && lex->foot->type == LEX_TP_OP)
		lex->foot->cannot_append = 1;
	return (1);
}

int		quoting(t_lexer *lex)
{
	if (!lex->quoted)
	{
		if (lex->line[lex->i] == '\\')
			lex->next_quoted = 1;
		else if (lex->line[lex->i] == '\'')
			lex->next_quoted = 2;
		else if (lex->line[lex->i] == '\"')
			lex->next_quoted = 3;
	}
	else if (lex->quoted == 1
			|| (lex->quoted == 2 && lex->line[lex->i] == '\'')
			|| (lex->quoted == 3 && lex->line[lex->i] == '\"'
				&& lex->line[lex->i - 1] != '\\'))
		lex->next_quoted = 0;
	return (1);
}

int		expansion(t_lexer *lex)
{
	if (lex->quoted)
		return (1);
	if (lex->next_expansion || lex->expansion_size > 0)
	{
		if (lex->line[lex->i] == '(' || lex->line[lex->i] == '{')
		{
			if (lex->expansion_size == EXPANSION_STACK_MAX)
				return (-1);
			lex->expansion_stack[lex->expansion_size++] = lex->line[lex->i];
		}
		lex->next_expansion = 0;
		if (lex->line[lex->i] == '$')
			return (1);
	}
	if (lex->expansion_size > 0)
	{
		if ((lex->expansion_stack[lex->expansion_size - 1] == '('
					&& lex->line[lex->i] == ')')
				|| (lex->expansion_stack[lex->expansion_size - 1] == '{'
					&& lex->line[lex->i] == '}'))
			lex->expansion_size--;
	}
	else if (lex->line[lex->i] == '$')
		lex->next_expansion = 1;
	return (1);
}
