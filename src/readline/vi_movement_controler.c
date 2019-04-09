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

	if (g_shell.edit.point_char->next->next)
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

}

void		vi_backward_word(void)
{

}

void		vi_end_word(void)
{

}