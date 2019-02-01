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

static int			(*g_lexer_func[])(t_lexer *) = {
	&lexer_operator,
	&lexer_quote,
	&lexer_blank,
	&lexer_word,
};

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
		lex->i++;
	}
	return (0);
}

int					lexer_token(t_lexer *lex, enum e_lexer_type)
{
	t_lexer_token	*t;

	if (!(ret = malloc(sizeof(*t))))
		return (-1);
	if (!(t->buffer = malloc(1)))
	{
		free(t);
		return (-1);
	}
	t->buffer[0] = lex->buffer[lex->i];
	t->size = 1;
	ft_memset(t, 0, sizeof(*t));
	t->buffer_position = lex->i;
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
** assumes a token exists
*/

int					lexer_append(t_lexer *lex, enum e_lexer_type type)
{
	uint8_t	*t;

	if (!(t = malloc(lex->foot->size + 1)))
		return (-1);
	ft_memcpy(t, lex->foot->buffer, lex->foot->size);
	lex->foot->buffer[lex->foot->size] = lex->buffer[lex->i];
	lex->foot->size++;
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
