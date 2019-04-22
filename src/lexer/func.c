/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 18:23:38 by emartine          #+#    #+#             */
/*   Updated: 2019/03/06 15:59:46 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

int		unquoted_backslash_newline(t_lexer *lex)
{
	if (!lex->quoted && lex->line[lex->i] == '\\')
	{
		if (lex->i == lex->line_size - 1)
			return (-1);
		if (lex->line[lex->i + 1] == '\n')
		{
			lex->backslash_newline = 1;
			lex->i++;
			return (0);
		}
	}
	return (1);
}

int		next_quoted(t_lexer *lex)
{
	lex->quoted = lex->next_quoted;
	return (1);
}

int		line_end(t_lexer *lex)
{
	if (lex->line[lex->i] != '\n')
		return (1);
	quoting(lex);
	if (!lex->quoted && lex->expansion_size == 0)
	{
		if (lex->foot)
			lex->foot->cannot_append = 1;
	}
	else if (word_append(lex) < 0)
		return (-1);
	if (!lex->backslash_newline && !lex->quoted
			&& lex->expansion_size == 0)
		lex->input_end = 1;
	return (0);
}
