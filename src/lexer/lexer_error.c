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
#include "parser.h"
#include <unistd.h>

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
