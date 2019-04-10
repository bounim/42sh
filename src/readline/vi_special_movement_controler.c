/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_special_movement_controler.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:16:41 by schakor           #+#    #+#             */
/*   Updated: 2019/04/05 14:55:51 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void		vi_forward_bigword(void)
{

}

void		vi_end_bigword(void)
{

}

void		vi_backward_bigword(void)
{

}

void		vi_move_first_nonblank(void)
{
	t_char	*tmp;

	tmp = g_shell.edit.char_list.head;
	while (tmp->is_prompt == TRUE)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->charac[0] != ' ')
			break ;
		tmp = tmp->next;
	}
	ft_putstr(tgoto(tgetstr("cm", NULL), tmp->x_pos, tmp->y_pos));
	g_shell.edit.point_char = tmp;
}

void		vi_move_counth_char(void)
{

}