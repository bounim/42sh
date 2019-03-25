/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_controler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:15:55 by aguillot          #+#    #+#             */
/*   Updated: 2019/03/11 14:32:53 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	supr_charac(void)
{
	t_char 			*curr;

	curr = g_shell.edit.point_char;
	if (!curr || curr == g_shell.edit.char_list.tail)
		return ;
	curr = curr->next;
	delete_char_from_list(curr);
	update_all_pos();
	clean_and_print();
}

void	del_charac(void)
{
	t_char 			*curr;
	struct winsize	max;
	int				t = 0;

	curr = g_shell.edit.point_char;
	max = g_shell.edit.term_info.max;
	if (!curr || curr->is_prompt == 1)
		return ;
	if (curr->prev && curr->prev->x_pos + 1 == max.ws_col
		&& curr->prev->y_pos + 2 == max.ws_row)
		t = 1;
	delete_char_from_list(curr);
	update_all_pos();
	clean_and_print();
	if (t == 1 && g_shell.edit.char_list.head->y_pos < 0)
	{
		write(1, "\n", 1);
		shift_pos_down(); //si on est tout en bas a gauche, que des t_char ne sont pas visibles parce que trop hauts et qu'on fait del, les y_pos vont prendre +1
	}
}

void	delete_backline(void)
{
	t_char	*curr;
	t_char	*end;
	int		c;

	if (g_shell.edit.point_char->is_prompt == 1)
		return ;
	curr = g_shell.edit.point_char;
	end = curr;
	c = 0;
	while (curr->prev->is_prompt == 0)
	{
		curr = curr->prev;
		c++;
	}
	g_shell.edit.cpy_buff = build_cpy_buff(curr, end);
	while (c >= 0)
	{
		del_charac();
		c--;
	}
}

void	delete_endline(void)
{
	t_char	*begin;

	if (g_shell.edit.point_char == g_shell.edit.char_list.tail)
		return ;
	begin = g_shell.edit.point_char->next;
	g_shell.edit.cpy_buff = build_cpy_buff(begin, g_shell.edit.char_list.tail);
	while (g_shell.edit.point_char->next)
		supr_charac();
}