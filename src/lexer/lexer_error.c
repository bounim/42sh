/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 18:52:29 by kberisha          #+#    #+#             */
/*   Updated: 2019/02/08 18:52:31 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <unistd.h>

static uint8_t		is_shift(uint8_t *buffer, size_t buffer_size)
{
	if (buffer_size > 2 || buffer[0] != '<' || buffer[0] != '>')
		return (0);
	if (buffer_size == 1)
		return (1);
	return (buffer[0] == buffer[1]);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	while (*s)
		ft_putchar(*s++);
}

t_lexer_token				*lexer_check(t_lexer *lex)
{
	t_lexer_token	*cur;

	cur = lex->head;
	if (cur && cur->type == LEX_TP_OP)
		return (cur);
	while (cur)
	{
		if (cur->type == 1 && cur->next && cur->next->type == 1)
		{
			if (cur->size == 1 && *cur->buffer == ';')
			{
				if (!is_shift(cur->next->buffer, cur->next->size))
					return (cur);
			}
			else
				return (cur);
		}
		cur = cur->next;
	}
	return (NULL);
}


/*	t_lexer_token	*current;

	current = lex->head;
	if (current->type == LEX_TP_OP)
		return (current->buffer);
	while (current)
	{
		if (current->type == LEX_TP_OP)
		{
			if (current->next && current->next->type == LEX_TP_OP)
			{
				if (current->size == 1 && *current->buffer == ';') // semicolon
				{
					if (!is_shift(current->next->buffer, current->next->size))
						return (current->buffer);
				}
				else // not semicolon
					return (current->buffer);
				if (!ft_memcmp(current->buffer, SEMICOLON, current->size) && !is_shift(current->next->buffer, current->next->size))
					return (current->buffer);
				else if (ft_memcmp(current->buffer, SEMICOLON, current->size))
					return (current->buffer);
			}
		}
		//if (current->next == NULL && ft_memcmp(current->buffer, SEMICOLON, current->size)) //on peut finir par un pipe aussi mais ouvre prompt et pas erreur
		//	return (current->buffer);
		current = current->next;
	}
	return (NULL);
}*/



void		lexer_print_error(t_lexer *lex)
{
	t_lexer_token		*tok;

	if ((tok = lexer_check(lex)))
	{
		ft_putstr("42sh: parse error near '");
		ft_putstr((char*)tok->buffer);
		ft_putstr("'\n");
	}
}
