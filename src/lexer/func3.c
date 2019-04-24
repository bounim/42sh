/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 16:23:07 by emartine          #+#    #+#             */
/*   Updated: 2019/03/30 16:23:08 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

int		operator_new(t_lexer *lex)
{
	uint8_t	ch;

	if (lex->quoted || lex->expansion_size > 0)
		return (1);
	ch = lex->line[lex->i];
	if ((ch == '<' || ch == '>') && lex->foot != NULL && lex->foot->is_number
			&& lex->i > 0 && (lex->line[lex->i - 1] >= '0'
				&& lex->line[lex->i - 1] <= '9'))
		lex->foot->type = LEX_TP_IO;
	if (ch == ';' || ch == '|' || ch == '&' || ch == '<' || ch == '>')
	{
		return (token(lex, LEX_TP_OP));
	}
	return (1);
}

int		unquoted_blank(t_lexer *lex)
{
	if (!lex->quoted && lex->expansion_size == 0
			&& (lex->line[lex->i] == ' ' || lex->line[lex->i] == '\t'))
	{
		if (lex->foot != NULL)
			lex->foot->cannot_append = 1;
		return (0);
	}
	return (1);
}

int		word_append(t_lexer *lex)
{
	if (lex->foot != NULL
			&& lex->foot->type == LEX_TP_WD && !lex->foot->cannot_append)
	{
		if (append(lex) < 0)
			return (-1);
		if (lex->foot->is_number
				&& (lex->line[lex->i] < '0' || lex->line[lex->i] > '9'))
			lex->foot->is_number = 0;
		return (0);
	}
	if (lex->expansion_size > 0)
		return (-1);
	return (1);
}

int		comment(t_lexer *lex)
{
	if (lex->line[lex->i] == '#')
	{
		while (lex->i < lex->line_size && lex->line[lex->i] != '\n')
			lex->i++;
		lex->i--;
		return (0);
	}
	return (1);
}

int		word_new(t_lexer *lex)
{
	if (token(lex, LEX_TP_WD) < 0)
		return (-1);
	if (lex->line[lex->i] >= '0' && lex->line[lex->i] <= '9')
		lex->foot->is_number = 1;
	return (0);
}
