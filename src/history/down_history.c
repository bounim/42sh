/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   down_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:37:42 by schakor           #+#    #+#             */
/*   Updated: 2019/04/22 16:52:13 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void		down_history_here(void)
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

void			get_next_history(void)
{
	if (!g_shell.hist.history)
		return ;
	if (g_shell.hist.history_save == -1 || g_shell.hist.history_save == -2)
		return ;
	switch_history();
	if (g_shell.hist.history_save == 0)
	{
		rl_free_controler(FREE_ONLY_EDIT_CHAR_LIST);
		g_shell.edit.point_char = NULL;
		g_shell.edit.cur_base_x = 0;
		init_char_list();
		init_prompt(g_shell.edit.prompt_id);
		clean_and_print();
		g_shell.hist.history_save = -1;
		return ;
	}
	else
	{
		g_shell.hist.history_save--;
		down_history_here();
	}
}

static void		vi_down_history_here(void)
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

void			vi_get_next_history(void)
{
	int			count;

	count = g_shell.edit.count;
	if (!g_shell.hist.history || g_shell.hist.history_save == -1
			|| g_shell.hist.history_save == -2)
		return ;
	switch_history();
	if (g_shell.hist.history_save == 0 || count > g_shell.hist.history_save)
	{
		rl_free_controler(FREE_ONLY_EDIT_CHAR_LIST);
		g_shell.edit.point_char = NULL;
		g_shell.edit.cur_base_x = 0;
		init_char_list();
		init_prompt(g_shell.edit.prompt_id);
		clean_and_print();
		g_shell.hist.history_save = -1;
		return ;
	}
	else
	{
		while (count-- && g_shell.hist.history_save > 0)
			g_shell.hist.history_save--;
		vi_down_history_here();
	}
}
