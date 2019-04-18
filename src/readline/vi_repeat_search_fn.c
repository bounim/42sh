/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_repeat_search_fn.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:19:05 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/11 13:19:06 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void		vi_repeat_after(uint8_t charac)
{
	t_char *curr;

	if (!(curr = g_shell.edit.point_char->next))
		return ;
	if (curr->charac[0] == charac)
		if (!(curr = curr->next))
			return ;
	while (curr)
	{
		if (charac == curr->charac[0])
		{
			ft_putstr(tgoto(tgetstr("cm", NULL), curr->x_pos, curr->y_pos));
			g_shell.edit.point_char = curr->prev;
			break ;
		}
		curr = curr->next;
	}
	g_shell.edit.vi_last_search_fn = SEARCH_CHAR_AFTER;
	g_shell.edit.vi_last_search_char = charac;
}

void		vi_repeat_before(uint8_t charac)
{
	t_char *curr;

	if (!(curr = g_shell.edit.point_char->next))
		return ;
	if (curr->charac[0] == charac)
		if ((curr = curr->prev) && curr->is_prompt)
			return ;
	while ((curr && curr->prev) && !curr->prev->is_prompt)
	{
		if (curr->charac[0] == charac)
		{
			ft_putstr(tgoto(tgetstr("cm", NULL), curr->x_pos, curr->y_pos));
			g_shell.edit.point_char = curr->prev;
			break ;
		}
		curr = curr->prev;
	}
	g_shell.edit.vi_last_search_fn = SEARCH_CHAR_BEFORE;
	g_shell.edit.vi_last_search_char = charac;
}

void		vi_repeat_after_before(uint8_t charac)
{
	t_char *curr;

	if (!(curr = g_shell.edit.point_char->next))
		return ;
	if (curr->charac[0] == charac)
		if (!(curr = curr->next))
			return ;
	while (curr)
	{
		if (curr->charac[0] == charac)
		{
			if ((curr = curr->prev) && curr->is_prompt)
				return ;
			ft_putstr(tgoto(tgetstr("cm", NULL), curr->x_pos, curr->y_pos));
			break ;
		}
		curr = curr->next;
	}
	g_shell.edit.vi_last_search_fn = SEARCH_CHAR_AFTER_BEFORE;
	g_shell.edit.vi_last_search_char = charac;
}

void		vi_repeat_before_after(uint8_t charac)
{
	t_char *curr;

	if (!(curr = g_shell.edit.point_char->next))
		return ;
	if (curr->charac[0] == charac)
		if ((curr = curr->prev) && curr->is_prompt)
			return ;
	while (curr && curr->prev && !curr->prev->is_prompt)
	{
		if (curr->charac[0] == charac)
		{
			if (!(curr = curr->next))
				return ;
			ft_putstr(tgoto(tgetstr("cm", NULL), curr->x_pos, curr->y_pos));
			g_shell.edit.point_char = curr->prev;
			break ;
		}
		curr = curr->prev;
	}
	g_shell.edit.vi_last_search_fn = SEARCH_CHAR_BEFORE_AFTER;
	g_shell.edit.vi_last_search_char = charac;
}
