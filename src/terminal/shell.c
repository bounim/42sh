/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 11:24:42 by schakor           #+#    #+#             */
/*   Updated: 2019/03/15 14:35:11 by khsadira         ###   ########.fr       */
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
	g_shell.hist.history_size = 0;
	g_shell.hist.history_save = -1;
	g_shell.hist.history = init_shell_history();
	g_shell.term_set = 0;
	g_shell.line_size = 0;
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
}

void					run_shell(void)
{
	t_bool run;

	char	*arg[5];
	t_opts	flag;
	int		i;

	arg[0] = "cd";
	arg[1] = "-apPflti";
	arg[2] = "salut les gens";
	arg[3] = 0;
	i = 0;
	i = check_opts(arg, &flag);
	printf("i = %d\n", i);
	printf("%d | %d | %d\n", flag.a, flag.pp, flag.f);
	run = TRUE;
	while (run == TRUE)
	{

		if (signal(SIGINT, ft_signal) < 0)
			fatal_exit(SH_EINVAL);
		if (signal(SIGABRT, ft_signal) < 0)
			fatal_exit(SH_EINVAL);
		readline(BASIC_PROMPT);
		if (g_shell.line && g_shell.edit.ret_ctrl_c == FALSE)
			lexer();
	}
}
