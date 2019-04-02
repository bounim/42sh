/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transpose_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 14:12:19 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/02 18:17:53 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static uint8_t	*create_buff_for_swap(t_char *curr)
{
	t_char		*tmp;
	uint8_t		*buff;

	tmp = curr;
	while (ft_u8_is_alnum(tmp->charac[0]))
		tmp = tmp->next;
	while (!ft_u8_is_alnum(tmp->charac[0]))
		tmp = tmp->next;
	while (tmp && ft_u8_is_alnum(tmp->charac[0]))
		tmp = tmp->next;
	buff = list_to_buff_print(curr, tmp);
	return (buff);
}

static void		swap_end_of_buff(t_char *curr, uint8_t *buff, size_t len,
	size_t c_len)
{
	while (ft_u8_is_alnum(buff[len]))
		len += ft_wchar_len(buff + len);
	while (!ft_u8_is_alnum(buff[len]))
	{
		c_len = ft_wchar_len(buff + len);
		ft_memmove(curr->charac, buff + len, c_len);
		curr->len = c_len;
		len += c_len;
		curr = curr->next;
	}
	len = 0;
	while (buff[len] && ft_u8_is_alnum(buff[len]) && curr)
	{
		c_len = ft_wchar_len(buff + len);
		ft_memmove(curr->charac, buff + len, c_len);
		curr->len = c_len;
		len += c_len;
		curr = curr->next;
	}
	if (curr)
		g_shell.edit.point_char = curr->prev;
	else
		g_shell.edit.point_char = g_shell.edit.char_list.tail;
}

static void		swap_words_in_list(t_char *curr, uint8_t *buff)
{
	size_t		len;
	size_t		c_len;

	len = ft_u8_strlen(buff) - 1;
	while (!(ft_u8_is_alnum(buff[len])))
		len--;
	while (ft_u8_is_alnum(buff[len]))
		len = go_back_one_car(buff, len);
	len += ft_wchar_len(buff + len);
	while (buff[len])
	{
		c_len = ft_wchar_len(buff + len);
		ft_memmove(curr->charac, buff + len, c_len);
		curr->len = c_len;
		len += c_len;
		curr = curr->next;
	}
	len = 0;
	swap_end_of_buff(curr, buff, len, c_len);
}

void			transpose_word(void)
{
	t_char		*curr;
	uint8_t		*buff;

	curr = g_shell.edit.point_char;
	buff = NULL;
	if (transpose_word_conditions(curr) == 0)
		return ;
	curr = get_to_right_position(curr);
	buff = create_buff_for_swap(curr);
	swap_words_in_list(curr, buff);
	free(buff);
	clean_and_print();
}
