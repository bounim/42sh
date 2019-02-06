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
#include <stdio.h>

int		main(void)
{
	char *line = "echo lol\n";
	t_lexer lex;
	t_printer_handle out;
	t_lexer_token *cur;

	printer_init(&out, 1);
	printf("<'%c'>\n", lexer_check_line((uint8_t *)line, ft_strlen(line)));
	lexer_init(&lex, (uint8_t *)line, ft_strlen(line));
	//if (lex.quote)
	//	printf("missing quoteeee\n");
	printer_int(&out, lexer_read(&lex));
	printer_str(&out, " - lex.i: ");
	printer_int(&out, lex.i);
	printer_str(&out, " - lex.nomatch: ");
	printer_int(&out, lex.nomatch);
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
			printer_str(&out, " buf='");
			printer_bin(&out, (char *)cur->buffer, cur->size);
			printer_str(&out, "'");
			printer_endl(&out);
			cur = cur->next;
		}
	}
	printer_flush(&out);
	lexer_destroy(&lex);
}
