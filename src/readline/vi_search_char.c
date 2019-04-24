/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_search_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:16:41 by schakor           #+#    #+#             */
/*   Updated: 2019/04/05 14:55:51 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void		vi_search_char_after(void)
{
	t_char	*curr;
	uint8_t	charac;

	if (read(0, &charac, 1) < 0 || !(curr = g_shell.edit.point_char->next))
		return ;
	if (curr->charac[0] == charac)
		if (!(curr = curr->next))
			return ;
	while (g_shell.edit.count--)
	{
		while (curr)
		{
			if (charac == curr->charac[0])
			{
				ft_putstr(tgoto(tgetstr("cm", NULL), curr->x_pos, curr->y_pos));
				g_shell.edit.point_char = curr->prev;
				curr = curr->next;
				break ;
			}
			curr = curr->next;
		}
	}
	g_shell.edit.vi_last_search_fn = SEARCH_CHAR_AFTER;
	g_shell.edit.vi_last_search_char = charac;
}

void		vi_search_char_before(void)
{
	t_char	*curr;
	uint8_t	charac;

	if (read(0, &charac, 1) < 0 || !(curr = g_shell.edit.point_char->next))
		return ;
	if (curr->charac[0] == charac)
		if ((curr = curr->prev) && curr->is_prompt)
			return ;
	while (g_shell.edit.count--)
	{
		while ((curr && curr->prev) && !curr->prev->is_prompt)
		{
			if (curr->charac[0] == charac)
			{
				ft_putstr(tgoto(tgetstr("cm", NULL), curr->x_pos, curr->y_pos));
				g_shell.edit.point_char = curr->prev;
				curr = curr->prev;
				break ;
			}
			curr = curr->prev;
		}
	}
	g_shell.edit.vi_last_search_fn = SEARCH_CHAR_BEFORE;
	g_shell.edit.vi_last_search_char = charac;
}

void		vi_search_char_after_before(void)
{
	t_char	*curr;
	t_char	*tmp;
	uint8_t	c;

	if (read(0, &c, 1) < 0 || !(curr = g_shell.edit.point_char->next))
		return ;
	if (curr->charac[0] == c)
		if (!(curr = curr->next))
			return ;
	while (g_shell.edit.count--)
	{
		while (curr)
		{
			if (curr->charac[0] == c && (tmp = curr->prev) && !tmp->is_prompt)
			{
				ft_putstr(tgoto(tgetstr("cm", NULL), tmp->x_pos, tmp->y_pos));
				g_shell.edit.point_char = tmp->prev;
				curr = curr->next;
				break ;
			}
			curr = curr->next;
		}
	}
	g_shell.edit.vi_last_search_fn = SEARCH_CHAR_AFTER_BEFORE;
	g_shell.edit.vi_last_search_char = c;
}

void		vi_search_char_before_after(void)
{
	t_char	*curr;
	t_char	*tmp;
	uint8_t c;

	if (read(0, &c, 1) < 0 || !(curr = g_shell.edit.point_char->next))
		return ;
	if (curr->charac[0] == c)
		if ((curr = curr->prev) && curr->is_prompt)
			return ;
	while (g_shell.edit.count--)
	{
		while (curr && curr->prev && !curr->prev->is_prompt)
		{
			if (curr->charac[0] == c && (tmp = curr->next))
			{
				ft_putstr(tgoto(tgetstr("cm", NULL), tmp->x_pos, tmp->y_pos));
				g_shell.edit.point_char = tmp->prev;
				curr = curr->prev;
				break ;
			}
			curr = curr->prev;
		}
	}
	g_shell.edit.vi_last_search_fn = SEARCH_CHAR_BEFORE_AFTER;
	g_shell.edit.vi_last_search_char = c;
}
