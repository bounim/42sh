/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_delete_controler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:20:17 by schakor           #+#    #+#             */
/*   Updated: 2019/04/05 19:53:58 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void		vi_delete_endline_insert_eol(void)
{
	delete_endline();
	go_to_end();
	g_shell.edit.edit_mode = MODE_VI_INSERT;
}

void		vi_clear_line_insert(void)
{
	t_char	*curr;
	t_char	*tmp;
	t_char	*prompt;

	curr = g_shell.edit.char_list.head;
	while (curr->is_prompt)
		curr = curr->next;
	prompt = curr->prev;
	while (curr)
	{
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	prompt->next = NULL;
	g_shell.edit.char_list.tail = prompt;
	g_shell.edit.point_char = g_shell.edit.char_list.tail;
	g_shell.edit.edit_mode = MODE_VI_INSERT;
	clean_and_print();
}

void		vi_delete_x(void)
{
	t_char	*tail;
	t_char	*begin;
	t_char	*tmp;
	int		count;

	count = g_shell.edit.count;
	if (!g_shell.edit.point_char ||
			!(begin = g_shell.edit.point_char->next))
		return ;
	tail = begin;
	while (--g_shell.edit.count && tail != g_shell.edit.char_list.tail)
		tail = tail->next;
	if (g_shell.edit.cpy_buff)
		free(g_shell.edit.cpy_buff);
	g_shell.edit.cpy_buff = build_cpy_buff(begin, tail);
	while (begin && count--)
	{
		tmp = begin;
		begin = begin->next;
		delete_char_from_list(tmp);
	}
	update_all_pos();
	clean_and_print();
	if (g_shell.edit.point_char == g_shell.edit.char_list.tail)
		move_left();
}

void		vi_delete_bigx(void)
{
	t_char	*tail;
	t_char	*beg;
	t_char	*tmp;
	int		count;

	count = g_shell.edit.count;
	if (!(tail = g_shell.edit.point_char) || tail->is_prompt)
		return ;
	beg = tail;
	while (--g_shell.edit.count && beg && beg->prev && !(beg->prev->is_prompt))
		beg = beg->prev;
	if (g_shell.edit.cpy_buff)
		free(g_shell.edit.cpy_buff);
	g_shell.edit.cpy_buff = build_cpy_buff(beg, tail);
	while (beg && count--)
	{
		tmp = beg;
		beg = beg->next;
		delete_char_from_list(tmp);
	}
	update_all_pos();
	clean_and_print();
	if (g_shell.edit.point_char == g_shell.edit.char_list.tail)
		move_left();
}
