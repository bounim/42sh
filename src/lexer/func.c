/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 18:23:38 by emartine          #+#    #+#             */
/*   Updated: 2019/02/01 18:23:40 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

#include <stdio.h> // XXX

int		unquoted_backslash_newline(t_lexer *lex)
{
	if (!lex->quoted && lex->i + 2 <= lex->line_size
			&& lex->line[lex->i] == '\\' && lex->line[lex->i] == '\n')
	{
		lex->i += 2;
		return (0);
	}
	return (1);
}

// FIXME where to consume newline???
int		heredoc(t_lexer *lex) // TODO do not forget about multiple heredoc support
{
	if (!lex->quoted && lex->heredoc) // TODO cmd <<EOF "quote
	{
		if (lex->i > 0 && lex->line[lex->i - 1] != '\n') // FIXME we got only one line anyway
		{
			lex->impl_error = 1;
			return (-1);
		}
		// TODO for << => append the whole line (until LF only) if line != delimiter (char by char because need to exec unquoted_backslash_newline)
		// TODO for <<- => skip TABS, then same as above (with line starting after tabs)
		// TODO or remove current element from heredoc_queue and heredoc--
		if (lex->heredoc_queue[0].skip_tabs)
		{
			while (lex->i < lex->line_size && lex->line[lex->i] == '\t')
				lex->i++;
		}
		lex->heredoc_queue[0].i = lex->i;
		while (lex->i < lex->line_size && lex->line[lex->i] != '\n')
			lex->i++;
		if (lex->i - lex->heredoc_queue[0].i
				== lex->heredoc_queue[0].delimiter_size
				&& ft_memcmp(lex->heredoc_queue[0].delimiter,
					lex->line + lex->heredoc_queue[0].i,
					lex->heredoc_queue[0].delimiter_size) == 0)
		{ // delimiter
			lex->heredoc--;
			lex->heredoc_queue++; // FIXME test
			//return (token(lex, TYPE_HEREDOC));
		}
		else // FIXME new token or append line??
		{
		}
	}
	return (1);
}

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
			&& lex->foot->type == TYPE_OPERATOR && ch != ';')
	{
		s = lex->foot->buffer_size;
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

int		operator_end(t_lexer *lex) // FIXME is it even useful
{
	if (lex->foot != NULL && lex->foot->type == TYPE_OPERATOR)
		lex->foot->cannot_append = 1;
	return (1);
}

int		quoting(t_lexer *lex) // FIXME is it ok to quote ' " (but != 1)
{
	if (!lex->quoted)
	{
		if (lex->line[lex->i] == '\\')
			lex->quoted = 1;
		else if (lex->line[lex->i] == '\'')
			lex->quoted = 2;
		else if (lex->line[lex->i] == '\"')
			lex->quoted = 3;
	}
	else if (lex->quoted == 1)
	{
		//lex->quoted = 0;
	}
	return (1);
}

int		expansion(t_lexer *lex)
{
	(void)lex;
	return (1);
}

int		operator_new(t_lexer *lex)
{
	uint8_t	ch;

	if (lex->quoted)
		return (1);
	ch = lex->line[lex->i];
	if (ch == ';' || ch == '|' || ch == '&' || ch == '<' || ch == '>')
		return (token(lex, TYPE_OPERATOR));
	return (1);
}

int		unquoted_blank(t_lexer *lex)
{
	if (!lex->quoted && (lex->line[lex->i] == ' ' || lex->line[lex->i] == '\t'))
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
			&& lex->foot->type == TYPE_WORD && !lex->foot->cannot_append)
	{
		// TODO somehow move to quoting()
		if (lex->quote_appended && (lex->quoted == 1
				|| (lex->quoted == 2 && lex->line[lex->i] == '\'')
				|| (lex->quoted == 3 && lex->line[lex->i] == '\"'
					&& lex->line[lex->i - 1] != '\\')))
		{
			lex->quoted = 0;
			lex->quote_appended = 0;
		}
		else if (lex->quoted && !lex->quote_appended)
			lex->quote_appended = 1;
		return (append(lex));
	}
	return (1);
}

int		comment(t_lexer *lex)
{
	if (lex->line[lex->i] == '#')
	{
		lex->i++;
		while (lex->i < lex->line_size && lex->line[lex->i] != '\n')
			lex->i++;
		return (0);
	}
	return (1);
}

int		word_new(t_lexer *lex)
{
	if (lex->quoted && !lex->quote_appended) // TODO somehow move to quoting()
		lex->quote_appended = 1;
	return (token(lex, TYPE_WORD));
}

int		line_end(t_lexer *lex)
{
	(void)lex;
	return (1);
}
