/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_controler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:15:08 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/04 14:53:54 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void		delete_char_from_list(t_char *curr)
{
	t_char	*next;
	t_char	*prev;

	next = curr->next;
	prev = curr->prev;
	free(curr);
	curr = NULL;
	if (next)
		next->prev = prev;
	else
		g_shell.edit.char_list.tail = prev;
	prev->next = next;
	g_shell.edit.point_char = prev;
	g_shell.edit.char_list.char_nb--;
}

static void	make_char_point(t_char *new_char, t_char *prev_char)
{
	t_char *tmp;

	tmp = NULL;
	if (prev_char == NULL)
	{
		g_shell.edit.char_list.head = new_char;
		g_shell.edit.char_list.tail = new_char;
		new_char->next = NULL;
		new_char->prev = NULL;
		return ;
	}
	new_char->prev = prev_char;
	tmp = prev_char->next;
	prev_char->next = new_char;
	new_char->next = tmp;
	if (tmp)
		tmp->prev = new_char;
	if (prev_char == g_shell.edit.char_list.tail)
		g_shell.edit.char_list.tail = new_char;
}

void		add_char_to_list(uint8_t *charac, size_t len, int is_prompt)
{
	t_char	*new_char;
	t_char	*prev_char;

	prev_char = g_shell.edit.point_char;
	if (!(new_char = malloc(sizeof(*new_char))))
		readline_errors_controler(MALLOC_ERROR);
	ft_memset(new_char, 0, sizeof(*new_char));
	ft_memmove(new_char->charac, charac, len);
	new_char->len = len;
	new_char->x_pos = get_x_pos(prev_char, g_shell.edit.term_info.max.ws_col);
	new_char->y_pos = get_y_pos(prev_char, g_shell.edit.term_info.max.ws_col,\
		g_shell.edit.term_info.max.ws_row);
	new_char->is_prompt = is_prompt;
	make_char_point(new_char, prev_char);
	update_all_pos();
	g_shell.edit.point_char = new_char;
	g_shell.edit.char_list.char_nb++;
}
