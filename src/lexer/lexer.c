/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 16:06:31 by emartine          #+#    #+#             */
/*   Updated: 2018/10/23 16:06:33 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

#include <stdio.h> // XXX
#include <unistd.h> // XXX
static int			(*g_lexer_func[])(t_lexer *) = {
	&lexer_operator,
	&lexer_quote,
	&lexer_inquote,
	&lexer_backslash,
	&lexer_blank,
	&lexer_word,
};

void		printstate(enum e_lexer_state st)
{
	if (st == LEX_ST_GEN)
		puts("ST_GEN");
	if (st == LEX_ST_OP)
		puts("ST_OP");
	if (st == LEX_ST_BLK)
		puts("ST_BLK");
	if (st == LEX_ST_QU)
		puts("ST_QU");
	if (st == LEX_ST_BS)
		puts("ST_BS");
	if (st == LEX_ST_WD)
		puts("ST_WD");
	if (st == LEX_ST_DLR)
		puts("ST_DLR");
	if (st == LEX_ST_NB)
		puts("ST_NB");
}

void				lexer_init(t_lexer *lex, uint8_t *buffer, size_t length)
{
	ft_memset(lex, 0, sizeof(*lex));
	lex->buffer = buffer;
	lex->buffer_length = length;
}

int					lexer_read(t_lexer *lex)
{
	size_t	f;
	int		r;

	lex->i = 0;
	while (lex->i < lex->buffer_length)
	{
		f = 0;
		printstate(lex->state);
		write(1, (char *)(lex->buffer + lex->i), 1);
		write(1, "\n", 1);
		while (f < sizeof(g_lexer_func) / sizeof(g_lexer_func[0]))
		{
			if ((r = g_lexer_func[f](lex)) < 0)
				return (-1);
			if (r == 0)
				break ;
			f++;
		}
		if (f == sizeof(g_lexer_func) / sizeof(g_lexer_func[0]))
		{
			lex->nomatch = 1;
			return (-1);
		}
		printf("lex quote = %d\n", lex->quote);
		lex->i++;
	}
	printf("lex quote = %d\n", lex->quote);
	if (lex->quote/* && (lex->state == LEX_ST_QU || lex->state == LEX_ST_BS)*/)
	{
		//lex->intoken = 1;
		puts("missing quote");
	}
	return (0);
}

int					lexer_token(t_lexer *lex, enum e_lexer_type type)
{
	t_lexer_token	*t;

	if (!(t = malloc(sizeof(*t))))
		return (-1);
	ft_memset(t, 0, sizeof(*t));
	if (!(t->buffer = malloc(1)))
	{
		free(t);
		return (-1);
	}
	t->buffer[0] = lex->buffer[lex->i];
	t->size = 1;
	t->buffer_position = lex->i;
	t->type = type;
	t->previous = lex->foot;
	t->next = NULL;
	if (lex->head)
		lex->foot->next = t;
	else
		lex->head = t;
	lex->foot = t;
	lex->intoken = 1;
	return (0);
}

/*
** assumes a token exists (tests anyway)
*/

int					lexer_append(t_lexer *lex, enum e_lexer_type type)
{
	uint8_t	*t;

	if (!lex->foot)
		return (-1);
	if (!(t = malloc(lex->foot->size + 1)))
		return (-1);
	ft_memcpy(t, lex->foot->buffer, lex->foot->size);
	free(lex->foot->buffer);
	lex->foot->buffer = t;
	lex->foot->buffer[lex->foot->size] = lex->buffer[lex->i];
	lex->foot->size++;
	lex->foot->type = type;
	return (0);
}

void				lexer_destroy(t_lexer *lex)
{
	t_lexer_token	*current;
	t_lexer_token	*previous;

	current = lex->head;
	while (current)
	{
		previous = current;
		current = current->next;
		free(previous->buffer);
		free(previous);
	}
	lex->head = NULL;
	lex->foot = NULL;
}
