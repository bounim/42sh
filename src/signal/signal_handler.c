/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 10:48:53 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/24 13:13:54 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void	window_modif(void)
{
	int	base_y;

	if (g_shell.edit.reading == FALSE)
		return ;
	g_shell.edit.cur_base_y = 0;
	g_shell.edit.cur_base_x = 0;
	clean_screen_from(0, 0);
	if ((ioctl(STDERR_FILENO, TIOCGWINSZ, &g_shell.edit.term_info.max)) == -1)
		readline_errors_controler(NO_TERM_INFO);
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

void		signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		(void)signo;
	}
	if (signo == SIGWINCH)
		window_modif();
}

void		init_signals(void)
{
	int	sig;

	sig = 1;
	while (sig < 32)
	{
		if (sig == SIGINT)
			signal(SIGINT, &signal_handler);
		else if (sig == SIGWINCH)
			signal(SIGWINCH, &signal_handler);
		else if (sig == SIGCHLD)
			signal(SIGCHLD, SIG_DFL);
		else
			signal(sig, SIG_IGN);
		sig++;
	}
}

void		clear_signals(void)
{
	int	sig;

	sig = 1;
	while (sig < 32)
	{
		signal(sig, SIG_DFL);
		sig++;
	}
}
