/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 10:48:53 by aguillot          #+#    #+#             */
/*   Updated: 2019/03/06 18:40:06 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void	window_modif(void)
{
	int base_y;

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

static void	stop_received(void)
{
	ioctl(STDERR_FILENO, TIOCSTI, "\x1A");
	signal(SIGTSTP, SIG_DFL);
	cooked_terminal();
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
	else if (signo == SIGINT)
	{
		ft_putstr(tgetstr("cr", NULL));
		//printf("\n\n\nx_pos: %u, y_pos: %d", g_shell.edit.char_list.tail->prev->x_pos, g_shell.edit.char_list.tail->prev->y_pos);
		printf("\n\n\nx_pos: %u, y_pos: %d", g_shell.edit.char_list.tail->prev->x_pos, g_shell.edit.char_list.tail->prev->y_pos);
		cooked_terminal();
		exit(0);
	}
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
