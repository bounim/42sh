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
	int		count;

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
	int		count;

	count = g_shell.edit.count;
	while (count-- && g_shell.edit.point_char->is_prompt == FALSE)
		move_left();
}

void		vi_forward_word(void)
{
	t_char	*curr;
	int		count;

	if (!(curr = g_shell.edit.point_char->next))
		return ;
	count = g_shell.edit.count;
	while (count-- && curr)
	{
		if (ft_isspace(curr->charac[0]))
		{
			while (curr && ft_isspace(curr->charac[0]))
				curr = curr->next;
		}
		else
		{
			while (curr && !ft_isspace(curr->charac[0]))
				curr = curr->next;
			while (curr && ft_isspace(curr->charac[0]))
				curr = curr->next;
		}
	}
	if (!curr)
		return (vi_go_to_end());
	ft_putstr(tgoto(tgetstr("cm", NULL), curr->x_pos, curr->y_pos));
	g_shell.edit.point_char = curr->prev;
}

void		vi_backward_word(void)
{
	t_char	*curr;
	int		count;

	curr = g_shell.edit.point_char;
	count = g_shell.edit.count;
	while (count-- && curr)
	{
		if (ft_isspace(curr->charac[0]))
		{
			while (curr && ft_isspace(curr->charac[0]))
				curr = curr->prev;
			while (curr && curr->prev && !ft_isspace(curr->prev->charac[0]))
				curr = curr->prev;
		}
		else
		{
			while (curr && curr->prev && !ft_isspace(curr->prev->charac[0]))
				curr = curr->prev;
		}
	}
	if (!curr || curr->is_prompt)
		return (go_to_home());
	ft_putstr(tgoto(tgetstr("cm", NULL), curr->x_pos, curr->y_pos));
	g_shell.edit.point_char = curr->prev;
}

void		vi_end_word(void)
{
	t_char	*curr;
	int		count;

	curr = g_shell.edit.point_char->next;
	count = g_shell.edit.count;
	while (count-- && curr)
	{
		if (curr->next && ft_isspace(curr->next->charac[0]))
		{
			curr = curr->next;
			while (curr && ft_isspace(curr->charac[0]))
				curr = curr->next;
			while (curr && curr->next && !ft_isspace(curr->next->charac[0]))
				curr = curr->next;
		}
		else
		{
			while (curr && curr->next && !ft_isspace(curr->next->charac[0]))
				curr = curr->next;
		}
	}
	if (!curr)
		return (vi_go_to_end());
	ft_putstr(tgoto(tgetstr("cm", NULL), curr->x_pos, curr->y_pos));
	g_shell.edit.point_char = curr->prev;
}
