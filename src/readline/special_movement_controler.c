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

void	go_to_end(void)
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

void	go_to_home(void)
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

void	jump_word_backward(void)
{
	t_char	*curr;
	int		x;
	int		y;

	curr = g_shell.edit.point_char;
	if (!curr || curr->is_prompt == 1)
		return ;
	while (curr && (curr->charac[0] == '\n'
		|| curr->charac[0] == ' '
		|| ft_memcmp(NBSP, curr->charac, 2) == 0) && curr->is_prompt == 0)
		curr = curr->prev;
	while (curr && curr->is_prompt == 0)
	{
		if (curr->charac[0] == '\n'
			|| curr->charac[0] == ' '
			|| ft_memcmp(NBSP, curr->charac, 2) == 0)
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

void	jump_word_forward(void)
{
	t_char	*curr;
	int		x;
	int		y;

	curr = g_shell.edit.point_char;
	if (!curr || curr == g_shell.edit.char_list.tail)
		return ;
	if (curr->charac[0] == ' ' || curr->charac[0] == '\n'
			|| ft_memcmp(NBSP, curr->charac, 2) == 0)
		curr = curr->next;
	while (curr && curr->next && curr->charac[0] != ' '
			&& curr->charac[0] != '\n' && ft_memcmp(NBSP, curr->charac, 2) != 0)
		curr = curr->next;
	while (curr && curr->next && (curr->next->charac[0] == ' '
				|| curr->next->charac[0] == '\n'
				|| ft_memcmp(NBSP, curr->next->charac, 2) == 0))
		curr = curr->next;
	x = get_x_pos(curr, g_shell.edit.term_info.max.ws_col);
	y = get_y_pos(curr, g_shell.edit.term_info.max.ws_col,\
		g_shell.edit.term_info.max.ws_row);
	ft_putstr(tgoto(tgetstr("cm", NULL), x, y));
	g_shell.edit.point_char = curr;
}
