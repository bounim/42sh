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
	g_shell.edit.prev_base_y = g_shell.edit.cur_base_y;
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

void	check_all_pos(void)
{
	t_char			*curr;
	struct winsize	max;

	curr = g_shell.edit.char_list.tail;
	max = g_shell.edit.term_info.max;
	if (curr->y_pos + 1 == max.ws_row
			&& (curr->x_pos + 1 == max.ws_col || curr->charac[0] == '\n'))
	{
		if (curr->charac[0] != '\n')
			write(1, "\n", 1);
		shift_pos_up();
	}
}

size_t	get_x_pos(t_char *prev_char, uint32_t col_limit)
{
	if (prev_char == NULL || prev_char->charac[0] == '\n' 
		|| prev_char->x_pos + 1 == col_limit)
		return (0);
	return (prev_char->x_pos + 1);
}


// !bonne: rajoute un y de trop en fin de ligne. Update, fixed that.
size_t	get_y_pos(t_char *prev_char, uint32_t col_limit, uint32_t row_limit)
{
	if (prev_char == NULL)
		return (g_shell.edit.cur_base_y);
	if (prev_char->x_pos + 2 == col_limit || prev_char->charac[0] == '\n')
	{
		if (prev_char->y_pos + 1 >= 0 && (uint32_t)(prev_char->y_pos + 1) == row_limit)
		{
			//on est sur la derniere position visible de l'echiquier. Dans ce cas la on veut simplement output le \n et shift pos up. Pas return +1
			shift_pos_up();//En faisant ca, la diff entre prev_base_y et base_y va prevenir print quil faut output le \n
		}
	}
	if (prev_char->x_pos + 1 == col_limit || prev_char->charac[0] == '\n')
		return (prev_char->y_pos + 1);
	return (prev_char->y_pos);
}

void	update_all_pos(void)
{
	t_char 			*curr;
	struct winsize	max;

	ioctl(STDERR_FILENO, TIOCGWINSZ, &max);
	curr = g_shell.edit.char_list.head;
	while (curr)
	{
		curr->x_pos = get_x_pos(curr->prev, max.ws_col);
		curr->y_pos = get_y_pos(curr->prev, max.ws_col, max.ws_row);
		curr = curr->next;
	}
}