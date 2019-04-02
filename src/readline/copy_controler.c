/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_controler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:14:25 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/02 19:06:04 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static size_t	get_cpy_size(t_char *cpy_begin, t_char *cpy_end)
{
	size_t cpy_size;

	cpy_size = 0;
	while (cpy_begin != cpy_end)
	{
		cpy_size += cpy_begin->len;
		if (cpy_begin->next == cpy_end)
			cpy_size += cpy_end->len;
		cpy_begin = cpy_begin->next;
	}
	return (cpy_size);
}

uint8_t			*build_cpy_buff(t_char *cpy_begin, t_char *cpy_end)
{
	t_char	*curr;
	size_t	cpy_size;
	uint8_t	*buff;
	int		i;

	curr = cpy_begin;
	cpy_size = get_cpy_size(curr, cpy_end);
	if (!(buff = (uint8_t*)malloc(sizeof(uint8_t) * (cpy_size + 1))))
		readline_errors_controler(MALLOC_ERROR);
	buff[cpy_size] = '\0';
	i = 0;
	while (curr && curr != cpy_end)
	{
		ft_memmove(buff + i, curr->charac, curr->len);
		i += curr->len;
		if (curr->next == cpy_end)
			ft_memmove(buff + i, curr->next->charac, curr->next->len);
		curr = curr->next;
	}
	return (buff);
}

void			paste_copy(void)
{
	uint8_t	*buff;
	int		i;
	size_t	len;

	buff = g_shell.edit.cpy_buff;
	i = 0;
	if (!buff || !buff[0])
		return ;
	while (buff[i])
	{
		len = ft_wchar_len(buff + i);
		add_char_to_list(buff + i, len, 0);
		update_all_pos();
		i += len;
	}
	clean_and_print();
}

void			copy_all_line(void)
{
	t_char	*cpy_begin;
	t_char	*cpy_end;
	uint8_t	*one_buf;

	one_buf = NULL;
	if (!(cpy_begin = find_first_non_prompt(g_shell.edit.char_list.head)))
		return ;
	if (!(cpy_end = g_shell.edit.char_list.tail))
		return ;
	if (cpy_begin == cpy_end)
	{
		if (!(one_buf = (uint8_t*)malloc(sizeof(uint8_t) * (cpy_end->len + 1))))
			fatal_exit(SH_ENOMEM);
		one_buf[cpy_end->len] = '\0';
		ft_memmove(one_buf, cpy_end->charac, cpy_end->len);
		g_shell.edit.cpy_buff = one_buf;
		return ;
	}
	if (g_shell.edit.cpy_buff)
	{
		free(g_shell.edit.cpy_buff);
		g_shell.edit.cpy_buff = NULL;
	}
	g_shell.edit.cpy_buff = build_cpy_buff(cpy_begin, cpy_end);
}

void			copy_current_word(void)
{
	t_char	*curr;
	t_char	*cpy_begin;
	t_char	*cpy_end;

	curr = g_shell.edit.point_char;
	if (copy_current_word_start_conditions(curr) == -1)
		return ;
	curr = curr->next;
	while (copy_current_word_begin_conditions(curr) == 1)
		curr = curr->prev;
	cpy_begin = curr;
	while (copy_current_word_end_conditions(curr) == 1)
		curr = curr->next;
	cpy_end = curr;
	if (g_shell.edit.cpy_buff)
	{
		free(g_shell.edit.cpy_buff);
		g_shell.edit.cpy_buff = NULL;
	}
	g_shell.edit.cpy_buff = build_cpy_buff(cpy_begin, cpy_end);
}
