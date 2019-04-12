/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 11:24:42 by schakor           #+#    #+#             */
/*   Updated: 2019/04/09 10:36:00 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void		init_shell(int ac, char **av, char **env)
{
	char	*term;

	(void)ac;
	(void)av;
	printer_init(&g_shell.out, 1);
	printer_init(&g_shell.err, 2);
	g_shell.el_mode = MODE_EMACS;
	g_shell.line = NULL;
	g_shell.envl = init_shell_envl(env);
	g_shell.alias = NULL;	
	g_shell.hist.history_size = 0;
	g_shell.hist.history_save = -1;
	g_shell.hist.history = init_shell_history();
	g_shell.term_set = 0;
	g_shell.line_size = 0;
	g_shell.term = STDIN_FILENO;
	g_shell.is_interactive = isatty(g_shell.term);
	g_shell.canonic_path = getcwd(NULL, 0);
	g_shell.stopped_proc = 0;
	if (!g_shell.is_interactive || !isatty(STDOUT_FILENO) ||\
			!isatty(STDERR_FILENO))
		fatal_exit(SH_ENOTTY);
	if (tcgetattr(g_shell.term, &(g_shell.cooked_tio)) == -1 ||\
			tcgetattr(g_shell.term, &(g_shell.raw_tio)) == -1)
		fatal_exit(SH_EINVAL);
	term = ft_strdup("xterm-256color");
	tgetent(NULL, term);
	g_shell.term_set = 1;
	/* job control start */
	while (tcgetpgrp(g_shell.term) != (g_shell.pgid = getpgrp()))
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
	tcsetpgrp(g_shell.term, g_shell.pgid);
	/*if (tcgetattr(g_shell.term, &(g_shell.cooked_tio)) == -1 ||\
			tcgetattr(g_shell.term, &(g_shell.raw_tio)) == -1)
		fatal_exit(SH_EINVAL);*/
	/* job control end */
	g_shell.raw_tio.c_lflag &= ~(ECHO | ICANON | ISIG);
	g_shell.raw_tio.c_oflag &= ~(OPOST);
	g_shell.raw_tio.c_cc[VMIN] = 1;
	g_shell.raw_tio.c_cc[VTIME] = 0;
	g_shell.debug_mode = 0;
}
