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

#include "twenty_one_sh.h"

t_shell				*g_shell;

int		main(int argc, char **argv, char **env)
{
	/*char *line = "echo lol\n";
	t_lexer lex;
	t_printer_handle out;
	t_lexer_token *cur;*/

	//printer_init(&out, 1);
	//printf("<'%c'>\n", lexer_check_line((uint8_t *)line, ft_strlen(line)));
	//lexer_init(&lex, (uint8_t *)line, ft_strlen(line));
	//printer_int(&out, lexer_read(&lex));
	//lexer_destroy(&lex);
	//if (lex.quote)
	//	printf("missing quoteeee\n");
	//printer_flush(&out);
	g_shell = init_shell(argc, argv, env);
	run_shell(g_shell);
	clean_shell(g_shell);
	exit(EXIT_SUCCESS);
}
