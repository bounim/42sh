/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_delete_motion_c.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:16:41 by schakor           #+#    #+#             */
/*   Updated: 2019/04/05 14:55:51 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static t_keymap		g_motion_keymap[MOTION_KEYMAP_SIZE] = {
	{" ", 1, vi_move_next_char},
	{"l", 1, vi_move_next_char},
	{"h", 1, vi_move_prev_char},
	{"w", 1, vi_forward_word},
	{"W", 1, vi_forward_bigword},
	{"e", 1, vi_end_word},
	{"E", 1, vi_end_bigword},
	{"b", 1, vi_backward_word},
	{"B", 1, vi_backward_bigword},
	{"^", 1, vi_move_first_nonblank},
	{"$", 1, vi_go_to_end},
	{"0", 1, go_to_home},
	{"|", 1, vi_move_counth_char},
	{"f", 1, vi_search_char_after},
	{"F", 1, vi_search_char_before},
	{"T", 1, vi_search_char_after_before},
	{"t", 1, vi_search_char_before_after},
	{";", 1, repeat_last_search_char},
	{",", 1, repeat_last_search_char_reverse},
	{"c", 1, vi_clear_line_insert}
};

static int		begin_is_before_end(t_char *begin, t_char *end)
{
	t_char		*tmp;

	tmp = begin;
	while (tmp)
	{
		if (tmp == end)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

static void		delete_from_to(t_char *begin, t_char *end)
{
	t_char		*tmp;
	int			begin_before_end;

	begin_before_end = begin_is_before_end(begin, end);
	if (begin_before_end)
	{
		while (begin && begin != end)
		{
			tmp = begin;
			begin = begin->next;
			delete_char_from_list(tmp);
		}
	}
	else
	{
		while (begin && begin != end)
		{
			tmp = begin;
			begin = begin->prev;
			delete_char_from_list(tmp);
		}
	}
	if (end)
		delete_char_from_list(end);
}

void			vi_delete_c(void)
{
	vi_delete_motion();
	vi_insert_mode();
}

void			vi_delete_motion(void)
{
	char	c;
	int		i;
	t_char	*begin;

	if (read(STDIN_FILENO, &c, 1) < 0 || (c != ' ' && c != '0' && c != 'b'
	&& c != 'F' && c != 'l' && c != 'W' && c != '^' && c != '$' && c != ';'
	&& c != 'E' && c != 'f' && c != 'T' && c != 'w' && c != '|' && c != ','
	&& c != 'B' && c != 'e' && c != 'h' && c != 't' && c != 'c'))
		return ;
	begin = g_shell.edit.point_char->next;
	i = 0;
	while (g_motion_keymap[i].seq && i < MOTION_KEYMAP_SIZE)
	{
		if (g_motion_keymap[i].seq[0] == c)
			g_motion_keymap[i].funckey();
		i++;
	}
	if (begin == g_shell.edit.point_char)
		return ;
	delete_from_to(begin, g_shell.edit.point_char);
	update_all_pos();
	clean_and_print();
}

void			vi_yank_motion(void)
{
	char	c;
	int		i;
	t_char	*cpy_begin;
	t_char	*cpy_end;

	if (read(STDIN_FILENO, &c, 1) < 0 || (c != ' ' && c != '0' && c != 'b'
	&& c != 'F' && c != 'l' && c != 'W' && c != '^' && c != '$' && c != ';'
	&& c != 'E' && c != 'f' && c != 'T' && c != 'w' && c != '|' && c != ','
	&& c != 'B' && c != 'e' && c != 'h' && c != 't' && c != 'c'))
		return ;
	cpy_begin = g_shell.edit.point_char->next;
	i = 0;
	while (g_motion_keymap[i].seq && i++ < MOTION_KEYMAP_SIZE)
	{
		if (g_motion_keymap[i].seq[0] == c)
			g_motion_keymap[i].funckey();
	}
	if (!g_shell.edit.point_char || cpy_begin == g_shell.edit.point_char)
		return ;
	if (g_shell.edit.cpy_buff)
		free(g_shell.edit.cpy_buff);
	cpy_end = g_shell.edit.point_char;
	g_shell.edit.cpy_buff = build_cpy_buff(cpy_begin, cpy_end);
	g_shell.edit.point_char = cpy_begin->prev;
	clean_and_print();
}
