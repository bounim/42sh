/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_special_movement_controler.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:16:41 by schakor           #+#    #+#             */
/*   Updated: 2019/04/11 13:29:38 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void		vi_forward_bigword(void)
{
	t_char	*curr;
	int		count;

	curr = g_shell.edit.point_char->next;
	count = g_shell.edit.count;
	while (count-- && curr)
	{
		while (curr && !ft_isspace(curr->charac[0]))
			curr = curr->next;
		while (curr && curr->next && ft_isspace(curr->charac[0]))
			curr = curr->next;
	}
	if (!curr)
		return (vi_go_to_end());
	ft_putstr(tgoto(tgetstr("cm", NULL), curr->x_pos, curr->y_pos));
	g_shell.edit.point_char = curr->prev;
}

void		vi_end_bigword(void)
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

void		vi_backward_bigword(void)
{
	t_char	*curr;
	int		count;

	curr = g_shell.edit.point_char;
	count = g_shell.edit.count;
	while (count-- && curr)
	{
		while (curr && ft_isspace(curr->charac[0]))
			curr = curr->prev;
		while (curr && curr->prev && !ft_isspace(curr->charac[0]))
			curr = curr->prev;
	}
	if (!curr || curr->is_prompt)
		return (go_to_home());
	ft_putstr(tgoto(tgetstr("cm", NULL), curr->next->x_pos, curr->next->y_pos));
	g_shell.edit.point_char = curr;
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
	if (!tmp)
		return ;
	ft_putstr(tgoto(tgetstr("cm", NULL), tmp->x_pos, tmp->y_pos));
	g_shell.edit.point_char = tmp->prev;
}

void		vi_move_counth_char(void)
{
	int		count;

	go_to_home();
	count = g_shell.edit.count - 1;
	while (count > 0)
	{
		if (g_shell.edit.point_char->next
			&& g_shell.edit.point_char->next->next)
			move_right();
		count--;
	}
}
