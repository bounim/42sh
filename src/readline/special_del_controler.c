/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_del_controler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <schakor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 16:57:30 by schakor           #+#    #+#             */
/*   Updated: 2019/04/02 18:33:53 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	eot_fn(void)
{
	if (g_shell.edit.char_list.tail->is_prompt == 1)
	{
		cooked_terminal();
		built_exit(NULL, NULL);
	}
	supr_charac();
}

void	delete_backline(void)
{
	t_char	*curr;
	t_char	*end;
	int		c;

	curr = g_shell.edit.point_char;
	if (curr->is_prompt == 1)
		return ;
	end = curr;
	c = 0;
	while (!curr->prev->is_prompt)
	{
		curr = curr->prev;
		c++;
	}
	if (g_shell.edit.cpy_buff)
		free(g_shell.edit.cpy_buff);
	g_shell.edit.cpy_buff = build_cpy_buff(curr, end);
	while (c-- >= 0)
		delete_char_from_list(g_shell.edit.point_char);
	if (g_shell.edit.cur_base_y < 0)
		place_base_at_start();
	update_all_pos();
	clean_and_print();
}

void	delete_endline(void)
{
	t_char *begin;

	if (g_shell.edit.point_char == g_shell.edit.char_list.tail)
		return ;
	begin = g_shell.edit.point_char->next;
	if (g_shell.edit.cpy_buff)
		free(g_shell.edit.cpy_buff);
	g_shell.edit.cpy_buff = build_cpy_buff(begin, g_shell.edit.char_list.tail);
	while (g_shell.edit.point_char->next)
	{
		begin = g_shell.edit.point_char->next;
		delete_char_from_list(begin);
	}
	update_all_pos();
	clean_and_print();
}

void	delete_word_forward(void)
{
	t_char	*curr;
	t_char	*tmp;

	if (!(curr = g_shell.edit.point_char->next) || curr->prev->y_pos < 0)
		return ;
	tmp = curr;
	while (tmp && (!ft_u8_is_alnum(tmp->charac[0])
		|| !ft_memcmp(tmp->charac, NBSP, 2)))
		tmp = tmp->next;
	while (tmp && tmp->next && ft_u8_is_alnum(tmp->next->charac[0])
		&& ft_memcmp(tmp->next->charac, NBSP, 2) != 0)
		tmp = tmp->next;
	if (g_shell.edit.cpy_buff)
		free(g_shell.edit.cpy_buff);
	if (!tmp)
		tmp = g_shell.edit.char_list.tail;
	g_shell.edit.cpy_buff = build_cpy_buff(curr, tmp);
	while (curr != tmp)
	{
		curr = curr->next;
		delete_char_from_list(curr->prev);
	}
	delete_char_from_list(curr);
	update_all_pos();
	clean_and_print();
}

void	delete_word_backward(void)
{
	t_char *curr;
	t_char *tmp;

	if (!(curr = g_shell.edit.point_char) && curr->prev->is_prompt)
		return ;
	tmp = curr;
	while (tmp && !tmp->prev->is_prompt && (!ft_u8_is_alnum(tmp->charac[0])
		|| !ft_memcmp(tmp->charac, NBSP, 2)))
		tmp = tmp->prev;
	while (tmp && !tmp->prev->is_prompt && (ft_u8_is_alnum(tmp->prev->charac[0])
		&& ft_memcmp(tmp->prev->charac, NBSP, 2) != 0))
		tmp = tmp->prev;
	if (tmp->y_pos < 0 || tmp->prev->y_pos < 0)
		return ;
	if (g_shell.edit.cpy_buff)
		free(g_shell.edit.cpy_buff);
	g_shell.edit.cpy_buff = build_cpy_buff(tmp, curr);
	while (tmp != curr)
	{
		curr = curr->prev;
		delete_char_from_list(curr->next);
	}
	delete_char_from_list(curr);
	update_all_pos();
	clean_and_print();
}
