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
#include <unistd.h>

int		main(void)
{
	uint8_t	line[1024];
	t_lexer lex;
	t_printer_handle out;
	t_lexer_token *cur;
	int		r;

	printer_init(&out, 1);
	while ((r = read(0, line, sizeof(line))) > 0)
	{
		printf("line = %s", line);
		//printf("<'%c'>\n", lexer_check_line(line, (size_t)r));
		if (line[r - 1] == '\n')
			r--;
		lexer_init(&lex, line, (size_t)r);
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
			printer_str(&out, "printing errors....\n");
			lexer_print_error(&lex);
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
		lexer_destroy(&lex);
		printer_flush(&out);
	}
}
