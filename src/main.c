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
#include "parser.h"
#include "expansion.h"
#include <stdio.h>
#include <unistd.h>

int		main(int ac, char **av, char **env)
{
	uint8_t						line[1024];
	t_lexer						lex;
	t_parser					parser;
	t_printer_handle	out;
	int		r;

	(void)ac;
	(void)av;
	printer_init(&out, 1);
	while ((r = read(0, line, sizeof(line))) > 0)
	{
		if (line[r - 1] == '\n')
			r--;
		lexer_init(&lex, line, (size_t)r);
		lexer_read(&lex);
		if (lex.head)
		{
			lexer_print_error(&lex);
			if (parser_create_tree(env, &parser, &lex) == -1)
				ft_putendl("error while parsing");
			// printf("parser_head = %p\n", parser.head);
			// do_expansions(env, parser.head);
		}
		lexer_destroy(&lex);
		printer_flush(&out);
	}
}
