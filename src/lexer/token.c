/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 21:26:06 by emartine          #+#    #+#             */
/*   Updated: 2019/03/06 21:26:08 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

int					token(t_lexer *lex, enum e_lexer_type type)
{
	t_lexer_token	*t;

	if (NULL == (t = malloc(sizeof(*t))))
		return (-1);
	ft_memset(t, 0, sizeof(*t));
	if (type == LEX_TP_WD || type == LEX_TP_OP)
	{
		if (NULL == (t->buffer = malloc(1)))
		{
			free(t);
			return (-1);
		}
		t->buffer[0] = lex->line[lex->i];
		t->size = 1;
	}
	else if (type == LEX_TP_HD) // FIXME called only when heredoc buffer == NULL?
	{
		//if (t->heredoc_queue[0].buffer == NULL)
		//if (NULL == (t->heredoc_queue[0].buffer = malloc(heredoc_queue[0].size + heredoc_queue[0].i - lex->i)))
		//if (NULL == (t->heredoc_queue[0].buffer = malloc(heredoc_queue[0].i - lex->i)))
	}
	t->line_x = lex->i;
	t->type = type;
	t->previous = lex->foot;
	t->next = NULL;
	if (lex->head)
		lex->foot->next = t;
	else
		lex->head = t;
	lex->foot = t;
	return (0);
}

/*
** assumes a token exists (tests anyway)
*/

int					append(t_lexer *lex)
{
	uint8_t	*t;

	if (!lex->foot || lex->foot->size == 0
			|| lex->foot->type == LEX_TP_HD)
	{
		lex->impl_error = 1;
		return (-1);
	}
	if (NULL == (t = malloc(lex->foot->size + 1)))
		return (-1);
	ft_memmove(t, lex->foot->buffer, lex->foot->size);
	free(lex->foot->buffer);
	t[lex->foot->size] = lex->line[lex->i];
	lex->foot->buffer = t;
	lex->foot->size++;
	return (0);
}
