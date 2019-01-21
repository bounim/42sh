/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 16:06:31 by emartine          #+#    #+#             */
/*   Updated: 2018/10/23 16:06:33 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		lexer_number(t_lexer *lex)
{
	t_lexer_token	*t;

	if (lex->buffer[lex->i] >= '0' && lex->buffer[lex->i] <= '9')
	{
		if (!(t = lexer_token(lex, LEX_IO_NUMBER)))
			return (-1);
		while (lex->buffer[lex->i] >= '0' && lex->buffer[lex->i] <= '9')
		{
			t->number = t->number * 10 + (lex->buffer[lex->i] - '0');
			t->in_buffer++;
		}
		lex->i += t->in_buffer;
		return (0);
	}
	return (1);
}
