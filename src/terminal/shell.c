/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 11:24:42 by schakor           #+#    #+#             */
/*   Updated: 2019/04/29 16:57:05 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	init_terminal(void)
{
	if (!isatty(g_shell.term)
			|| !isatty(STDOUT_FILENO) || !isatty(STDERR_FILENO))
		return (-1);
	while (tcgetpgrp(g_shell.term) != (g_shell.pgid = getpgrp()))
		kill(-g_shell.pgid, SIGTTIN);
	init_signals();
	g_shell.pgid = getpid();
	if (setpgid(g_shell.pgid, g_shell.pgid) < 0
			|| tcsetpgrp(g_shell.term, g_shell.pgid) < 0
			|| tcgetattr(g_shell.term, &g_shell.cooked_tio) < 0
			|| tcgetattr(g_shell.term, &g_shell.raw_tio) < 0)
		return (-1);
	return (0);
}

static char	*get_progname(char *arg0)
{
	char	*ret;

	ret = arg0;
	while (*arg0)
	{
		if (*arg0 == '/')
			ret = arg0 + 1;
		arg0++;
	}
	return (ret);
}

void		init_shell(int ac, char **av, char **env)
{
	(void)ac;
	ft_memset(&g_shell, 0, sizeof(g_shell));
	printer_init(&g_shell.out, STDOUT_FILENO);
	printer_init(&g_shell.err, STDERR_FILENO);
	g_shell.progname = get_progname((!av[0] || !av[0][0]) ? "21sh" : av[0]);
	g_shell.term = STDIN_FILENO;
	if (init_terminal() < 0)
		fatal_exit(SH_ENOTTY);
	g_shell.term_set = 1;
	g_shell.raw_tio.c_lflag &= ~(ECHO | ICANON | ISIG | ECHOCTL);
	g_shell.raw_tio.c_cc[VMIN] = 1;
	g_shell.raw_tio.c_cc[VTIME] = 0;
	tgetent(NULL, "xterm-256color");
	g_shell.el_mode = MODE_EMACS;
	g_shell.envl = init_shell_envl(env);
	g_shell.hist.history_save = -1;
	g_shell.hist.history = init_shell_history();
	if (NULL == (g_shell.canonic_path = getcwd(NULL, 0))
			|| hashmap_init(&g_shell.hmap, HASHMAP_SIZE,
				hashmap_hash_crc32) < 0)
		fatal_exit(SH_EINVAL);
}
