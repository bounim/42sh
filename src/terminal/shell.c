/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 11:24:42 by schakor           #+#    #+#             */
/*   Updated: 2019/03/13 12:26:33 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void					init_shell(int ac, char **av, char **env)
{
	char				*term;

	(void)ac;
	(void)av;
	g_shell.el_mode = MODE_EMACS;
	g_shell.line = NULL;
	g_shell.envl = init_shell_envl(env);
	g_shell.history_save = -1;
	g_shell.history_size = 0;
	g_shell.history = init_shell_history();
	g_shell.term_set = 0;
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO) ||\
			!isatty(STDERR_FILENO))
		fatal_exit(SH_ENOTTY);
	if (!(term = get_env_val(g_shell.envl, "TERM")))
		return ;
	if (!tgetent(NULL, term))
		return ;
	g_shell.term_set = 1;
	if (tcgetattr(STDIN_FILENO, &(g_shell.cooked_tio)) ||\
			tcgetattr(STDIN_FILENO, &(g_shell.raw_tio)))
		fatal_exit(SH_EINVAL);
	g_shell.raw_tio.c_lflag &= ~(ECHO | ICANON | ISIG);
	g_shell.raw_tio.c_oflag &= ~(OPOST);
	g_shell.raw_tio.c_cc[VMIN] = 1;
	g_shell.raw_tio.c_cc[VTIME] = 0;
	g_shell.canonic_path = NULL;
}

static void				parse_command(uint8_t *line, size_t len)
{
	t_lexer 		lex;
	t_lexer_token	*cur;

	lexer_init(&lex, line, len);
	printer_int(&g_shell.err, lexer_read(&lex));
	printer_endl(&g_shell.err);
	printer_flush(&g_shell.err);
	if (lex.head)
	{
		cur = lex.head;
		while (cur)
		{
			printer_str(&g_shell.out, "token=");
			printer_int(&g_shell.out, (int)cur->type);
			printer_str(&g_shell.out, " line_y=");
			printer_ulong(&g_shell.out, cur->line_y);
			printer_str(&g_shell.out, " line_x=");
			printer_ulong(&g_shell.out, cur->line_x);
			/*printer_str(&g_shell.out, " buf='");
			printer_bin(&g_shell.out, (char *)cur->buffer, cur->size);
			printer_str(&g_shell.out, "'");*/
			printer_endl(&g_shell.out);
			cur = cur->next;
		}
	}
	lexer_destroy(&lex);
}

void					run_shell(void)
{
	t_bool run;
	char *arg[5];
	char	*str[4];
	char	*retest[3];

	printf("la\n");
	arg[0] = "setenv";
	arg[1] = "NEWTEST";
	arg[2] = "/etc";
	arg[3] = NULL;
	arg[4] = NULL;
	str[0] = "unsetenv";
	str[1] = "TEST";
	str[2] = "NEWTEST";
	str[3] = NULL;
	retest[0] = "unset";
	retest[1] = "HOME";
	retest[2] = NULL;

	push_env(&g_shell.envl, "HOME", "khsadira",  0);
	run = TRUE;
	while (run == TRUE)
	{
		if (signal(SIGINT, ft_signal) < 0)
			fatal_exit(SH_EINVAL);
		if (signal(SIGABRT, ft_signal) < 0)
			fatal_exit(SH_EINVAL);
		readline();
		write(1, "\n", 1);
		if (g_shell.line)
		{
			parse_command(g_shell.line, ft_u8_strlen(g_shell.line));
/*			printf("-------PRINT_ENV----------\n\n");
			print_envl(g_shell.envl);
			printf("\n\n------SETENV--------\n\n");
			built_setenv(arg, &g_shell.envl);
			printf("\n\n------PRINT_ENV--------\n\n");
			print_envl(g_shell.envl);
			printf("\n\n------UNSETENV--------\n\n");
			built_unsetenv(str, &g_shell.envl);
			printf("\n\n------SET--------\n\n");
			built_set(g_shell.envl);
			printf("\n\n------UNSET--------\n\n");
			built_unset(retest, &g_shell.envl);
			printf("\n\n------SET--------\n\n");
			built_set(g_shell.envl);*/
			//ft_putstr((char*)g_shell.line);
			//write(1, "\n", 1);
			if (ft_u8_strequ(g_shell.line, (const uint8_t *)"history"))
				;
			else if (ft_u8_strequ(g_shell.line, (const uint8_t *)"exit"))
				exit(EXIT_SUCCESS);
		}
	}
}
