/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_controler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:14:25 by aguillot          #+#    #+#             */
/*   Updated: 2019/03/11 17:05:22 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

size_t	get_cpy_size(t_char *cpy_begin, t_char *cpy_end)
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

uint8_t	*build_cpy_buff(t_char *cpy_begin, t_char *cpy_end)
{
	t_char 	*curr;
	size_t 	cpy_size;
	uint8_t	*buff;
	int		i;

	curr = cpy_begin;
	cpy_size = get_cpy_size(curr, cpy_end);
	if (!(buff = (uint8_t*)malloc(sizeof(uint8_t) * (cpy_size + 1))))
		line_editing_errors_controler(MALLOC_ERROR);
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

void	paste_copy(void)
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
		clean_and_print();
		i += len;
	}
}

void	copy_all_line(void)
{
	t_char	*curr;
	t_char	*cpy_begin;
	t_char 	*cpy_end;

	curr = find_first_non_prompt(g_shell.edit.char_list.head);
	if ((cpy_begin = curr) == NULL)
		return ;
	if ((cpy_end = g_shell.edit.char_list.tail) == NULL)
		return ;
	if (g_shell.edit.cpy_buff)
	{
		free(g_shell.edit.cpy_buff);
		g_shell.edit.cpy_buff = NULL;
	}
	g_shell.edit.cpy_buff = build_cpy_buff(cpy_begin, cpy_end);
}

void	copy_current_word(void)
{
	t_char 	*curr;
	t_char	*cpy_begin;
	t_char	*cpy_end;
	
	curr = g_shell.edit.point_char;
	if (!curr->next || (curr->next && (curr->next->charac[0] == ' '
		|| curr->next->charac[0] == '\n' || curr->next->charac[0] == '	'
		|| ft_memcmp(curr->next->charac, NBSP, 2) == 0)))
		return ;
	curr = curr->next;
	while (curr->prev->is_prompt == 0 && (curr->prev->charac[0] != ' '
		&& curr->prev->charac[0] != '\n' && curr->prev->charac[0] != '	'
		&& ft_memcmp(curr->prev->charac, NBSP, 2) != 0))
		curr = curr->prev;
	cpy_begin = curr;
	while (curr->next && (curr->next->charac[0] != ' '
		&& curr->next->charac[0] != '\n'
		&& curr->next->charac[0] != '	'
		&& ft_memcmp(curr->next->charac, NBSP, 2) != 0))
		curr = curr->next;
	cpy_end = curr;
	if (g_shell.edit.cpy_buff)
	{
		free(g_shell.edit.cpy_buff);
		g_shell.edit.cpy_buff = NULL;
	}
	g_shell.edit.cpy_buff = build_cpy_buff(cpy_begin, cpy_end);
}