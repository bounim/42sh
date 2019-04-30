/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:38:20 by schakor           #+#    #+#             */
/*   Updated: 2019/04/22 16:09:29 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void		up_history_here(void)
{
	int			i;
	t_history	*head;

	head = g_shell.hist.history;
	i = 0;
	while (i < g_shell.hist.history_save && g_shell.hist.history->bfr)
	{
		g_shell.hist.history = g_shell.hist.history->bfr;
		i++;
	}
	print_history();
	g_shell.hist.history = head;
}

void			get_prev_history(void)
{
	if (!g_shell.hist.history)
		return ;
	if (listlen(g_shell.hist.history) == g_shell.hist.history_save + 1)
		return ;
	if (g_shell.hist.history_save == -2)
		return ;
	if (g_shell.hist.history_save >= 0)
		switch_history();
	if (g_shell.hist.history_save == -1)
	{
		print_history();
		g_shell.hist.history_save = 0;
	}
	else
	{
		if (listlen(g_shell.hist.history) != g_shell.hist.history_save + 1)
			g_shell.hist.history_save++;
		up_history_here();
	}
}

void			vi_get_prev_history(void)
{
	int			count;

	count = g_shell.edit.count;
	while (count--)
		get_prev_history();
}
