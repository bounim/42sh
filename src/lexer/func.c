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

int		heredoc(t_lexer *lex) // TODO do not forget about multiple heredoc support
{
	if (!lex->quoted && lex->heredoc) // TODO cmd <<EOF "quote
	{
		// TODO for << => append the whole line if line != delimiter
		// TODO for <<- => skip TABS, then same as above (with line starting after tabs)
	}
	return (1);
}
