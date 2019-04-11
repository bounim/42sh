/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_movement_controler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:16:41 by schakor           #+#    #+#             */
/*   Updated: 2019/04/05 14:55:51 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void		vi_move_next_char(void)
{
	int			count;

	if (g_shell.edit.point_char->next)
	{
		count = g_shell.edit.count;
		while (count && g_shell.edit.point_char->next->next)
		{
			move_right();
			count--;
		}
	}
}

void		vi_move_prev_char(void)
{
	int 		count;

	count = g_shell.edit.count;
	while (count-- && g_shell.edit.point_char->is_prompt == FALSE)
		move_left();
}

void		vi_forward_word(void)
{
	t_char	*tmp;
	int		count;
	int		x;
	int		y;

	if (!(tmp = g_shell.edit.point_char->next) || tmp->prev->y_pos < 0)
		return ;
	count = g_shell.edit.count;
	while (count-- && tmp)
	{
		while (tmp && (!ft_u8_is_alnum(tmp->charac[0])))
			tmp = tmp->next;
		while (tmp && tmp->next && ft_u8_is_alnum(tmp->next->charac[0]))
			tmp = tmp->next;
	}
	x = get_x_pos(tmp, g_shell.edit.term_info.max.ws_col);
	y = get_y_pos(tmp, g_shell.edit.term_info.max.ws_col,\
		g_shell.edit.term_info.max.ws_row);
	ft_putstr(tgoto(tgetstr("cm", NULL), x, y));
	g_shell.edit.point_char = tmp;
}

void		vi_backward_word(void)
{
	t_char	*curr;
	int 	count;
	int		x;
	int		y;

	curr = g_shell.edit.point_char;
	count = g_shell.edit.count;
	if (!curr || curr->is_prompt == 1)
		return ;
	while (count--)
	{
		while (curr && !ft_u8_is_alnum(curr->charac[0]) && curr->is_prompt == 0)
			curr = curr->prev;
		while (curr && curr->is_prompt == 0) {
			if (!ft_u8_is_alnum(curr->charac[0]))
				break;
			curr = curr->prev;
		}
	}
	x = get_x_pos(curr, g_shell.edit.term_info.max.ws_col);
	if ((y = get_y_pos(curr, g_shell.edit.term_info.max.ws_col,\
		g_shell.edit.term_info.max.ws_row)) < 0)
		return ;
	ft_putstr(tgoto(tgetstr("cm", NULL), x, y));
	g_shell.edit.point_char = curr;
}

void		vi_end_word(void)
{

}