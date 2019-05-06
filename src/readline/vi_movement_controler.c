/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_movement_controler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:16:41 by schakor           #+#    #+#             */
/*   Updated: 2019/05/06 19:00:54 by schakor          ###   ########.fr       */
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
	t_char	*cur;

	if (!(cur = g_shell.edit.point_char->next))
		return ;
	while (g_shell.edit.count-- && cur)
	{
		if (cur && (ft_isalnum(cur->charac[0]) || cur->charac[0] == '_'))
		{
			while (cur && (ft_isalnum(cur->charac[0]) || cur->charac[0] == '_'))
				cur = cur->next;
		}
		else if (cur && !ft_isspace(cur->charac[0]))
		{
			while (cur && !ft_isalnum(cur->charac[0])
				&& cur->charac[0] != '_' && !ft_isspace(cur->charac[0]))
				cur = cur->next;
		}
		while (cur && ft_isspace(cur->charac[0]))
			cur = cur->next;
	}
	if (!cur)
		return (vi_go_to_end());
	ft_putstr(tgoto(tgetstr("cm", NULL), cur->x_pos, cur->y_pos));
	g_shell.edit.point_char = cur->prev;
}

void		vi_backward_word(void)
{
	t_char *cur;

	cur = g_shell.edit.point_char;
	while (g_shell.edit.count-- && cur)
	{
		while (cur && (ft_isspace(cur->charac[0]))
		&& !cur->prev->is_prompt)
			cur = cur->prev;
		if (cur && (ft_isalnum(cur->charac[0]) || cur->charac[0] == '_'))
		{
			while (cur && (ft_isalnum(cur->charac[0]) || cur->charac[0] == '_')
					&& !cur->is_prompt)
				cur = cur->prev;
		}
		else if (cur && !(ft_isspace(cur->charac[0])))
		{
			while (cur && (!(ft_isspace(cur->charac[0])))
					&& !ft_isalnum(cur->charac[0]) && !cur->is_prompt)
				cur = cur->prev;
		}
	}
	if (!cur || cur->is_prompt || !cur->next)
		return (go_to_home());
	g_shell.edit.point_char = cur;
	ft_putstr(tgoto(tgetstr("cm", NULL), cur->next->x_pos, cur->next->y_pos));
}

void		vi_end_word(void)
{
	t_char	*curr;

	if (!g_shell.edit.point_char || !(curr = g_shell.edit.point_char->next))
		return ;
	while (g_shell.edit.count-- && curr)
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
