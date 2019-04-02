/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_controler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:15:55 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/02 19:10:13 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	supr_charac(void)
{
	t_char	*curr;

	curr = g_shell.edit.point_char;
	if (!curr || curr == g_shell.edit.char_list.tail)
		return ;
	curr = curr->next;
	if (!curr->next && curr->x_pos == 0 && curr->y_pos == 0)
	{
		g_shell.edit.point_char = curr;
		del_charac();
		return ;
	}
	delete_char_from_list(curr);
	update_all_pos();
	clean_and_print();
}

void	del_charac(void)
{
	t_char			*curr;
	struct winsize	max;
	int				t;

	t = 0;
	curr = g_shell.edit.point_char;
	max = g_shell.edit.term_info.max;
	if (!curr || curr->is_prompt == 1)
		return ;
	if (curr->prev && curr->prev->x_pos + 1 == max.ws_col
		&& (curr->prev->y_pos + 2 == max.ws_row
		|| g_shell.edit.char_list.head->y_pos < 0))
		t = 1;
	delete_char_from_list(curr);
	update_all_pos();
	if (t == 1 && g_shell.edit.char_list.head->y_pos < 0)
	{
		write(1, "\n", 1);
		shift_pos_down();
	}
	clean_and_print();
}
