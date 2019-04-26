/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 21:26:06 by emartine          #+#    #+#             */
/*   Updated: 2019/04/26 14:18:29 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"
#include "lexer_internal.h"

static inline void	token_init(t_lexer *lex, enum e_lexer_type type,
		t_lexer_token *t)
{
	t->line_x = lex->i;
	t->type = type;
	t->previous = lex->foot;
	t->next = NULL;
	if (lex->head)
		lex->foot->next = t;
	else
		lex->head = t;
	lex->foot = t;
	t->redir_input = -1;
}

int					token(t_lexer *lex, enum e_lexer_type type)
{
	t_lexer_token	*t;

	if (NULL == (t = malloc(sizeof(*t))))
		return (-1);
	ft_memset(t, 0, sizeof(*t));
	if (type == LEX_TP_WD || type == LEX_TP_OP)
	{
		if (NULL == (t->buffer = malloc(1 + 1)))
		{
			free(t);
			return (-1);
		}
		t->buffer[0] = lex->line[lex->i];
		t->buffer[1] = '\0';
		t->size = 1;
	}
	token_init(lex, type, t);
	return (0);
}

/*
** assumes a token exists (tests anyway)
*/

int					append(t_lexer *lex)
{
	uint8_t	*t;

	if (!lex->foot || lex->foot->size == 0)
		return (-1);
	if (NULL == (t = malloc(lex->foot->size + 1 + 1)))
		return (-1);
	ft_memmove(t, lex->foot->buffer, lex->foot->size);
	free(lex->foot->buffer);
	t[lex->foot->size] = lex->line[lex->i];
	t[lex->foot->size + 1] = '\0';
	lex->foot->buffer = t;
	lex->foot->size++;
	return (0);
}
