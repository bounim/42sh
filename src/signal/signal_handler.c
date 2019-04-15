/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 10:48:53 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/11 15:47:49 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void	window_modif(void)
{
	int 			base_y;

	g_shell.edit.cur_base_y = 0;
	g_shell.edit.cur_base_x = 0;
	clean_screen_from(0, 0);
	//window_modif_test();
	if (!g_shell.edit.char_list.head)
		return ;
	if ((ioctl(STDERR_FILENO, TIOCGWINSZ, &g_shell.edit.term_info.max)) == -1)
		readline_errors_controler(NO_TERM_INFO);
	if ((g_shell.edit.term_info.max.ws_row < 15  && g_shell.edit.term_info.max.ws_col < 40)
		|| g_shell.edit.term_info.max.ws_row < 10 || g_shell.edit.term_info.max.ws_col < 30)
	{
		write(1, "Window too small.\n\rWaiting for resize.", 38);
		init_signals();
		while (42)
		{
			if (signal(SIGWINCH, &signal_handler))
				return ;
		}
	}
	base_y = g_shell.edit.cur_base_y;
	while (base_y)
	{
		ft_putstr(tgetstr("sf", NULL));
		base_y--;
	}
	g_shell.edit.cur_base_x = 0;
	g_shell.edit.cur_base_y = 0;
	update_all_pos();
	clean_and_print();
}

static void	stop_received(void)
{
	int status;

	WIFSTOPPED(status);
	ioctl(STDERR_FILENO, TIOCSTI, "\x1A");
	signal(SIGTSTP, SIG_DFL);
	cooked_terminal();
	mark_proc_status(g_shell.stopped_proc, status);
}

static void	cont_received(void)
{
	init_signals();
	raw_terminal();
	window_modif();
}

void		signal_handler(int signo)
{
	if (signo == SIGWINCH)
		window_modif();
	else if (signo == SIGTSTP)
		stop_received();
	else if (signo == SIGCONT)
		cont_received();
	else if (signo > 0 && signo < 33)
	{
		free_controler(FREE_ALL_AND_EXIT);
		cooked_terminal();
		exit(1);
	}
}

void	init_signals(void)
{
	int i;

	i = 0;
	while (++i < 33)
		signal(i, &signal_handler);
}
