/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_movement_controler.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:18:07 by aguillot          #+#    #+#             */
/*   Updated: 2019/03/06 19:11:15 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void		vi_go_to_end(void)
{
	t_char	*tail;

	tail = g_shell.edit.char_list.tail;
	ft_putstr(tgoto(tgetstr("cm", NULL), tail->x_pos, tail->y_pos));
	g_shell.edit.point_char = tail->prev;
}

void		go_to_end(void)
{
	t_char	*curr;
	int		x;
	int		y;

	curr = g_shell.edit.char_list.head;
	if (!curr)
		return ;
	while (curr && curr->next)
		curr = curr->next;
	x = get_x_pos(curr, g_shell.edit.term_info.max.ws_col);
	y = get_y_pos(curr, g_shell.edit.term_info.max.ws_col,\
		g_shell.edit.term_info.max.ws_row);
	ft_putstr(tgoto(tgetstr("cm", NULL), x, y));
	g_shell.edit.point_char = curr;
}

void		go_to_home(void)
{
	t_char	*curr;
	int		x;
	int		y;

	curr = g_shell.edit.char_list.head;
	if (!curr)
		return ;
	while (curr && curr->is_prompt)
		curr = curr->next;
	if (!curr)
		return ;
	curr = curr->prev;
	x = get_x_pos(curr, g_shell.edit.term_info.max.ws_col);
	y = get_y_pos(curr, g_shell.edit.term_info.max.ws_col,\
		g_shell.edit.term_info.max.ws_row);
	if (y < 0)
		return ;
	ft_putstr(tgoto(tgetstr("cm", NULL), x, y));
	g_shell.edit.point_char = curr;
}

void		jump_word_backward(void)
{
	t_char	*curr;
	int		x;
	int		y;

	curr = g_shell.edit.point_char;
	if (!curr || curr->is_prompt == 1)
		return ;
	while (curr && !ft_u8_is_alnum(curr->charac[0]) && curr->is_prompt == 0)
		curr = curr->prev;
	while (curr && curr->is_prompt == 0)
	{
		if (!ft_u8_is_alnum(curr->charac[0]))
			break ;
		curr = curr->prev;
	}
	x = get_x_pos(curr, g_shell.edit.term_info.max.ws_col);
	if ((y = get_y_pos(curr, g_shell.edit.term_info.max.ws_col,\
		g_shell.edit.term_info.max.ws_row)) < 0)
		return ;
	ft_putstr(tgoto(tgetstr("cm", NULL), x, y));
	g_shell.edit.point_char = curr;
}

void		jump_word_forward(void)
{
	int		x;
	int		y;
	t_char	*curr;
	t_char	*tmp;

	if (!(curr = g_shell.edit.point_char->next) || curr->prev->y_pos < 0)
		return ;
	tmp = curr;
	while (tmp && (!ft_u8_is_alnum(tmp->charac[0])
	|| !ft_memcmp(tmp->charac, NBSP, 2)))
		tmp = tmp->next;
	while (tmp && tmp->next && ft_u8_is_alnum(tmp->next->charac[0])
	&& ft_memcmp(tmp->next->charac, NBSP, 2) != 0)
		tmp = tmp->next;
	x = get_x_pos(tmp, g_shell.edit.term_info.max.ws_col);
	y = get_y_pos(tmp, g_shell.edit.term_info.max.ws_col,\
		g_shell.edit.term_info.max.ws_row);
	ft_putstr(tgoto(tgetstr("cm", NULL), x, y));
	g_shell.edit.point_char = tmp;
}
