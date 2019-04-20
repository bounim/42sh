/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_pos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:16:10 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/02 19:11:42 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	shift_pos_up(void)
{
	t_char	*curr;

	curr = g_shell.edit.char_list.head;
	g_shell.edit.lines_to_shift++;
	g_shell.edit.cur_base_y--;
	while (curr)
	{
		curr->y_pos--;
		curr = curr->next;
	}
}

void	shift_pos_down(void)
{
	t_char	*curr;

	curr = g_shell.edit.char_list.head;
	g_shell.edit.cur_base_y++;
	while (curr)
	{
		curr->y_pos++;
		curr = curr->next;
	}
}

size_t	get_x_pos(t_char *prev_char, uint32_t col_limit)
{
	if (prev_char == NULL || prev_char->charac[0] == '\n'
		|| prev_char->x_pos + 1 == col_limit)
		return (0);
	return (prev_char->x_pos + 1);
}

size_t	get_y_pos(t_char *prev_char, uint32_t col_limit, uint32_t row_limit)
{
	if (prev_char == NULL)
		return (g_shell.edit.cur_base_y);
	if (prev_char->x_pos + 2 == col_limit || prev_char->charac[0] == '\n')
	{
		if ((prev_char->charac[0] == '\n' || prev_char->y_pos + 1 >= 0)
		&& (uint32_t)(prev_char->y_pos + 1) == row_limit)
			shift_pos_up();
	}
	if (prev_char->x_pos + 1 == col_limit || prev_char->charac[0] == '\n')
		return (prev_char->y_pos + 1);
	return (prev_char->y_pos);
}

void	update_all_pos(void)
{
	t_char			*curr;
	struct winsize	max;

	if (ioctl(STDERR_FILENO, TIOCGWINSZ, &max) < 0)
		return ;
	curr = g_shell.edit.char_list.head;
	while (curr)
	{
		curr->x_pos = get_x_pos(curr->prev, max.ws_col);
		curr->y_pos = get_y_pos(curr->prev, max.ws_col, max.ws_row);
		curr = curr->next;
	}
}
