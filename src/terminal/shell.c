/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 11:24:42 by schakor           #+#    #+#             */
/*   Updated: 2019/03/26 15:11:42 by khsadira         ###   ########.fr       */
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
	g_shell.term = STDIN_FILENO;
	g_shell.is_interactive = isatty(g_shell.term);
	if (!g_shell.is_interactive || !isatty(STDOUT_FILENO) ||\
			!isatty(STDERR_FILENO))
		fatal_exit(SH_ENOTTY);
	if (!(term = get_env_val(g_shell.envl, "TERM")))
		return ;
	if (!tgetent(NULL, term))
		return ;
	g_shell.term_set = 1;
	/* job control start */
	while (my_tcgetpgrp(g_shell.term) != (g_shell.pgid = getpgrp()))
		kill(-g_shell.pgid, SIGTTIN);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
	g_shell.pgid = getpid();
	g_shell.state = -1;
	if (setpgid(g_shell.pgid, g_shell.pgid) < 0)
	{
		ft_putstr_fd("Couldn't put the shell in its own process group\n", 2);
		exit (1);
	}
	my_tcsetpgrp(g_shell.term, g_shell.pgid);
	if (tcgetattr(g_shell.term, &(g_shell.cooked_tio)) ||\
			tcgetattr(g_shell.term, &(g_shell.raw_tio)))
		fatal_exit(SH_EINVAL);
	/* job control end */
	g_shell.raw_tio.c_lflag &= ~(ECHO | ICANON | ISIG);
	g_shell.raw_tio.c_oflag &= ~(OPOST);
	g_shell.raw_tio.c_cc[VMIN] = 1;
	g_shell.raw_tio.c_cc[VTIME] = 0;
	g_shell.debug_mode = 0;
}

void					run_shell(void)
{
	t_bool run;

	run = TRUE;
	while (run == TRUE)
	{

		if (signal(SIGINT, ft_signal) < 0)
			fatal_exit(SH_EINVAL);
		if (signal(SIGABRT, ft_signal) < 0)
			fatal_exit(SH_EINVAL);
		readline(BASIC_PROMPT);
		printf("debug mode : %zu\n", g_shell.debug_mode);
		if (g_shell.line && g_shell.edit.ret_ctrl_c == FALSE)
			lexer();
	}
}
