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
	}
	return (0);
}

t_lexer_token		*lexer_token(t_lexer *lex)
{
	t_lexer_token	*ret;

	if (!(ret = malloc(sizeof(*ret))))
		return (NULL);
	ft_memset(ret, 0, sizeof(*ret));
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
		free(previous);
	}
	lex->head = NULL;
	lex->foot = NULL;
}
