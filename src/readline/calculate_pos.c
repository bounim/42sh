/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_pos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:16:10 by aguillot          #+#    #+#             */
/*   Updated: 2019/03/06 18:40:06 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	shift_pos_up(void)
{
	t_char	*curr;

	curr = g_shell.edit.char_list.head;
	g_shell.edit.cur_base_y--;
	while (curr)
	{
		curr->y_pos--;
		curr = curr->next;
	}
}

size_t	get_x_pos(t_char *prev_char)
{
	if (prev_char == NULL || prev_char->charac[0] == '\n'
			|| prev_char->x_pos + 1 == g_shell.edit.term_info.max.ws_col)
		return (0);
	return (prev_char->x_pos + 1);
}

size_t	get_y_pos(t_char *prev_char)
{
	if (prev_char == NULL)
		return (g_shell.edit.cur_base_y);
	if (prev_char->x_pos + 1 == g_shell.edit.term_info.max.ws_col
		|| prev_char->charac[0] == '\n')
		return (prev_char->y_pos + 1);
	if (prev_char->x_pos + 1 < g_shell.edit.term_info.max.ws_col)
		return (prev_char->y_pos);
	return (prev_char->y_pos);
}

void	update_all_pos(void)
{
	t_char *curr;

	curr = g_shell.edit.char_list.head;
	while (curr)
	{
		curr->x_pos = get_x_pos(curr->prev);
		curr->y_pos = get_y_pos(curr->prev);
		curr = curr->next;
	}
}