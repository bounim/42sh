/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 16:06:31 by emartine          #+#    #+#             */
/*   Updated: 2018/10/23 16:06:33 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		lexer_operator(t_lexer *lex)
{
	t_lexer_token		*t;
	enum e_lexer_token	li;

	li = LEXER_FIRST_OP;
	while (g_lexer_token_str[li]->s)
	{
		if (lex->buffer_length - lex->i >= g_lexer_token_str[li]->l)
		{
			if (memcmp(&lex->buffer[lex->i], g_lexer_token_str[li]->s,
						g_lexer_token_str[li]->l) == 0)
			{
				if (!(t = lexer_token(lex, li)))
					return (-1);
				t->in_buffer = g_lexer_token_str[li]->l;
				lex->i += t->in_buffer;
				return (0);
			}
		}
		li++;
	}
	return (1);
}
