/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 16:06:31 by emartine          #+#    #+#             */
/*   Updated: 2018/10/23 16:06:33 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		lexer_newline(t_lexer *lex)
{
	t_lexer_token	*t;

	if (lex->buffer[lex->i] == '\n')
	{
		if (!(t = lexer_token(lex, LEX_NEWLINE)))
			return (-1);
		t->in_buffer = 1;
		lex->i += t->in_buffer;
		return (0);
	}
	return (1);
}
