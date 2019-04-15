/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_yank_paste.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:20:17 by schakor           #+#    #+#             */
/*   Updated: 2019/04/05 19:53:58 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void		vi_yank_endline(void)
{
	t_char	*curr;
	t_char	*tail;

	curr = g_shell.edit.point_char->next;
	tail = g_shell.edit.char_list.tail;
	if (g_shell.edit.point_char == tail)
		return ;
	g_shell.edit.cpy_buff = build_cpy_buff(curr, tail);
}

void		vi_paste_after(void)
{
	int		count;

	count = g_shell.edit.count;
	while (count--)
	{
		move_right();
		paste_copy();
		move_left();
	}
}

void		vi_paste_before(void)
{
	int		count;

	count = g_shell.edit.count;
	while (count--)
	{
		paste_copy();
		move_left();
	}
}
