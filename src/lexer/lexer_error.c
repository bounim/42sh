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

static uint8_t		is_shift(uint8_t *buffer)
{
	return (buffer == LESS || buffer == GREAT || buffer == DLESS
			|| buffer == DGREAT);
}

uint8_t				*lexer_check(t_lexer *lex)
{
	t_lexer_token	*current;

	current = lex->head;
	if (current->type == OP)
		return (current->buffer);
	while (current)
	{
		if (current->type == OP)
		{
			if (current->next && current->next->type == OP)
			{
				if (current->buffer == SEMICOLON && !is_shift(current->next->buffer))
					return (current->buffer);
				else if (current->buffer != SEMICOLON)
					return (current->buffer);
			}
		}
		if (current->next == NULL && current->buffer != SEMICOLON) //on peut finir par un pipe aussi mais ouvre prompt et pas erreur
			return (current->buffer)
		current = current->next;
	}
	return (NULL);
}

void		lexer_print_error(t_lexer *lex)
{
	uint8_t		*buffer;

	if ((buffer = lexer_check(lex)))
	{
		printf("21sh: parse error near unexpected token '%s'", buffer);
	}
}
