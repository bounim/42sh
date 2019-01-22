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

int		lexer_space(t_lexer *lex)
{
	t_lexer_token	*t;

	if (lex->buffer[lex->i] == ' ' || lex->buffer[lex->i] == '\t')
	{
		if (!(t = lexer_token(lex, LEX_SPACE)))
			return (-1);
		t->in_buffer = 1;
		while (lex->buffer[lex->i + t->in_buffer]
				&& (lex->buffer[lex->i + t->in_buffer] == ' '
					|| lex->buffer[lex->i + t->in_buffer] == '\t'))
			t->in_buffer++;
		lex->i += t->in_buffer;
		return (0);
	}
	return (1);
}
