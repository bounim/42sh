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

char * const g_lexer_token_str[] = {
	"foo\n",
	"bar",
};

void				lexer_init(t_lexer *lex, char *buffer, size_t length)
{
	ft_memset(lex, 0, sizeof(*lex));
	lex->buffer = buffer;
	lex->buffer_length = length;
}

static int			(*g_lexer_func[])(t_lexer *) = {
	&lexer_space,
	&lexer_quote,
	&lexer_number,
	&lexer_newline,
};

int					lexer_read(t_lexer *lex)
{
	size_t	i_copy;
	size_t	f;

	lex->i = 0;
	while (lex->i < lex->buffer_length)
	{
		i_copy = lex->i;
		f = 0;
		while (f < sizeof(g_lexer_func) / sizeof(g_lexer_func[0]))
		{
			if (g_lexer_func[f](lex) < 0)
				return (-1);
			f++;
		}
		if (lex->i == i_copy)
		{
			lex->nomatch = 1;
			return (-1);
		}
	}
	return (0);
}

t_lexer_token		*lexer_token(t_lexer *lex, enum e_lexer_token token)
{
	t_lexer_token	*ret;

	if (!(ret = malloc(sizeof(*ret))))
		return (NULL);
	ft_memset(ret, 0, sizeof(*ret));
	ret->token = token;
	ret->buffer_position = lex->i;
	ret->previous = lex->foot;
	ret->next = NULL;
	if (lex->head)
		lex->foot->next = ret;
	else
		lex->head = ret;
	lex->foot = ret;
	return (ret);
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
		if (previous->string)
			free(previous->string);
		free(previous);
	}
	lex->head = NULL;
	lex->foot = NULL;
}
