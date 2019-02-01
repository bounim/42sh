/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 16:06:31 by emartine          #+#    #+#             */
/*   Updated: 2018/10/23 16:06:33 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

int		main(void)
{
	char buffer[] =
		"< <> 'foo' \n"
		"'bar';";
	t_lexer lex;
	t_printer_handle out;
	t_lexer_token *cur;

	printer_init(&out, 1);
	lexer_init(&lex, (uint8_t *)buffer, sizeof(buffer) - 1);
	printer_int(&out, lexer_read(&lex));
	printer_str(&out, " - lex.i: ");
	printer_int(&out, lex.i);
	printer_endl(&out);
	if (lex.head)
	{
		cur = lex.head;
		while (cur)
		{
			printer_str(&out, "token=");
			printer_int(&out, (int)cur->type);
			printer_str(&out, " bufpos=");
			printer_ulong(&out, cur->buffer_position);
			printer_endl(&out);
			cur = cur->next;
		}
	}
	printer_flush(&out);
	lexer_destroy(&lex);
}
