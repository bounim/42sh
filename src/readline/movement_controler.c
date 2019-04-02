/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_controler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:17:09 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/02 18:42:07 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	move_up(void)
{
	t_char	*curr;
	int		x;
	int		y;

	curr = g_shell.edit.point_char;
	if (!curr || curr->prev->is_prompt == 1)
		return ;
	x = curr->x_pos;
	curr = curr->prev;
	y = curr->y_pos;
	while (curr && curr->is_prompt == 0 && curr->y_pos <= y)
	{
		if (curr->x_pos == (uint32_t)x)
			break ;
		curr = curr->prev;
	}
	x = get_x_pos(curr, g_shell.edit.term_info.max.ws_col);
	y = get_y_pos(curr, g_shell.edit.term_info.max.ws_col,\
		g_shell.edit.term_info.max.ws_row);
	if (y < 0)
		return ;
	ft_putstr(tgoto(tgetstr("cm", NULL), x, y));
	g_shell.edit.point_char = curr;
}

void	move_down(void)
{
	t_char	*curr;
	int		x;
	int		y;

	curr = g_shell.edit.point_char;
	if (!curr || !curr->next)
		return ;
	x = curr->x_pos;
	curr = curr->next;
	y = curr->y_pos + 1;
	while (curr && curr->next && curr->y_pos <= y)
	{
		if (curr->x_pos == (uint32_t)x)
			break ;
		curr = curr->next;
	}
	if (!curr)
		curr = g_shell.edit.char_list.tail;
	x = get_x_pos(curr, g_shell.edit.term_info.max.ws_col);
	y = get_y_pos(curr, g_shell.edit.term_info.max.ws_col,\
		g_shell.edit.term_info.max.ws_row);
	ft_putstr(tgoto(tgetstr("cm", NULL), x, y));
	g_shell.edit.point_char = curr;
}

void	move_right(void)
{
	t_char	*curr;
	int		x;
	int		y;

	curr = g_shell.edit.point_char->next;
	if (!curr)
		return ;
	x = get_x_pos(curr, g_shell.edit.term_info.max.ws_col);
	y = get_y_pos(curr, g_shell.edit.term_info.max.ws_col,\
		g_shell.edit.term_info.max.ws_row);
	g_shell.edit.point_char = curr;
	ft_putstr(tgoto(tgetstr("cm", NULL), x, y));
}

void	move_left(void)
{
	t_char	*prev;
	int		x;
	int		y;

	prev = g_shell.edit.point_char;
	if (prev == NULL || prev->is_prompt == 1)
		return ;
	x = prev->x_pos;
	y = prev->y_pos;
	if (y < 0)
		return ;
	g_shell.edit.point_char = prev->prev;
	ft_putstr(tgoto(tgetstr("cm", NULL), x, y));
}

void	exchange_point_mark(void)
{
	t_char	*tmp;

	tmp = g_shell.edit.mark;
	g_shell.edit.mark = g_shell.edit.point_char;
	g_shell.edit.point_char = tmp;
	place_cursor_after_print(g_shell.edit.point_char,\
	g_shell.edit.term_info.max.ws_col, g_shell.edit.term_info.max.ws_row);
}
