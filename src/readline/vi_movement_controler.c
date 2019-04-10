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
	t_char	*curr;
	int		count;

	curr = g_shell.edit.point_char->next;
	count = g_shell.edit.count;
	while (count-- && curr)
	{
		if (ft_u8_is_alnum(curr->charac[0]))
		{
			while (curr && ft_u8_is_alnum(curr->charac[0]))
				curr = curr->next;
		}
		else
		{
			while (curr && !ft_u8_is_alnum(curr->charac[0]))
				curr = curr->next;
		}
	}
	if (curr)
	{
		ft_putstr(tgoto(tgetstr("cm", NULL), curr->x_pos, curr->y_pos));
		g_shell.edit.point_char = curr->prev;
	}
}

void		vi_backward_word(void)
{

}

void		vi_end_word(void)
{

}