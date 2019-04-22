/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 11:24:42 by schakor           #+#    #+#             */
/*   Updated: 2019/04/22 17:25:55 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void		init_shell_end(void)
{
	if (!g_shell.is_interactive || !isatty(STDOUT_FILENO)
			|| !isatty(STDERR_FILENO))
		fatal_exit(SH_ENOTTY);
	if (tcgetattr(g_shell.term, &(g_shell.cooked_tio)) == -1
			|| tcgetattr(g_shell.term, &(g_shell.raw_tio)) == -1)
		fatal_exit(SH_EINVAL);
	tgetent(NULL, "xterm-256color");
	g_shell.term_set = 1;
	g_shell.raw_tio.c_lflag &= ~(ECHO | ICANON | ISIG);
	g_shell.raw_tio.c_oflag &= ~(OPOST);
	g_shell.raw_tio.c_cc[VMIN] = 1;
	g_shell.raw_tio.c_cc[VTIME] = 0;
	g_shell.debug_mode = 0;
}

void		init_shell(int ac, char **av, char **env)
{
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
	init_shell_end();
}
