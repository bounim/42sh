/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 16:27:09 by emartine          #+#    #+#             */
/*   Updated: 2018/12/10 16:27:11 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		lexer_quote(t_lexer *lex)
{
	t_lexer_token	*t;

	if (lex->buffer[lex->i] == '\'')
	{
		if (!(t = lexer_token(lex, LEX_WORD)))
			return (-1);
		t->in_buffer = 1;
		while (lex->buffer[lex->i + t->in_buffer]
				&& lex->buffer[lex->i + t->in_buffer] != '\'')
			t->in_buffer++;
		if (lex->buffer[lex->i + t->in_buffer] != '\'')
		{
			lex->quote = 1;
			return (-1);
		}
		t->in_buffer++;
		lex->i += t->in_buffer;
		return (0);
	}
	return (1);
}
