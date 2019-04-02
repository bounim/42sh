/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drag_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 16:27:23 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/02 18:51:41 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	switch_nodes(t_char *curr)
{
	t_char tmp;

	if (!curr->next)
		return ;
	tmp = *curr;
	ft_memmove(curr->charac, curr->next->charac, curr->next->len);
	curr->len = curr->next->len;
	ft_memmove(curr->next->charac, tmp.charac, tmp.len);
	curr->next->len = tmp.len;
}

void	drag_char(void)
{
	t_char *curr;

	curr = g_shell.edit.point_char;
	if (!curr || (curr->is_prompt == 1 && !curr->next))
		return ;
	if (curr->is_prompt == 0 && curr->prev->is_prompt == 1 && !curr->next)
	{
		move_right();
		return ;
	}
	if (curr == g_shell.edit.char_list.tail)
		curr = curr->prev;
	else if (curr->is_prompt == 1)
	{
		curr = curr->next;
		move_right();
	}
	switch_nodes(curr);
	clean_and_print();
	move_right();
}
