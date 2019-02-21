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

#include "lexer_internal.h"

#include <stdio.h> // XXX
#include <unistd.h> // XXX

static int			(*g_lexer_func[])(t_lexer *) = {
	unquoted_backslash_newline,
	heredoc,
	operator_append,
	operator_end,
	quoting,
	expansion,
	operator_new,
	unquoted_blank,
	word_append,
	comment,
	word_new,
};

void				lexer_init(t_lexer *lex, uint8_t *line, size_t line_size)
{
	ft_memset(lex, 0, sizeof(*lex));
	lex->line = line;
	lex->line_size = line_size;
}

void				lexer_newline(t_lexer *lex, uint8_t *line, size_t line_size)
{
	lex->line = line;
	lex->line_size = line_size;
	lex->line_y++;
	lex->i = 0;
}

int					lexer_read(t_lexer *lex)
{
	size_t	f;
	int		r;

	lex->i = 0;
	while (lex->i < lex->line_size)
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
			lex->impl_error = 1;
			return (-1);
		}
		lex->i++;
	}
	if (line_end(lex) < 0)
		return (-1);
	return (parser(lex));
}

int					token(t_lexer *lex, enum e_lexer_type type)
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
	t->buffer[0] = lex->line[lex->i];
	t->size = 1;
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

int					append(t_lexer *lex, enum e_lexer_type type)
{
	uint8_t	*t;

	if (!lex->foot)
	{
		lex->impl_error = 1;
		return (-1);
	}
	if (!(t = malloc(lex->foot->size + 1)))
		return (-1);
	ft_memcpy(t, lex->foot->buffer, lex->foot->size);
	free(lex->foot->buffer);
	lex->foot->buffer = t;
	lex->foot->buffer[lex->foot->size] = lex->line[lex->i];
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
	// TODO destroy parser?
}
