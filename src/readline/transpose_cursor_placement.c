/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transpose_cursor_placement.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 18:55:36 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/02 18:23:50 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

size_t			go_back_one_car(uint8_t *buff, size_t index)
{
	index--;
	if (index > 0)
	{
		while (buff[index] && buff[index] >= 128 && buff[index] <= 191)
			index--;
	}
	return (index);
}

static int		is_there_word_after(t_char *curr)
{
	int t;

	t = 0;
	while (curr && !ft_u8_is_alnum(curr->charac[0]))
	{
		t = 1;
		curr = curr->next;
	}
	while (curr && ft_u8_is_alnum(curr->charac[0]))
	{
		if (t == 1)
			return (1);
		curr = curr->next;
	}
	while (curr && !ft_u8_is_alnum(curr->charac[0]))
		curr = curr->next;
	if (curr)
		return (1);
	return (0);
}

static t_char	*go_back_two_words(t_char *curr)
{
	while (!ft_u8_is_alnum(curr->charac[0]) && !curr->prev->is_prompt)
		curr = curr->prev;
	while (ft_u8_is_alnum(curr->charac[0]) && !curr->prev->is_prompt)
		curr = curr->prev;
	while (!ft_u8_is_alnum(curr->charac[0]) && !curr->prev->is_prompt)
		curr = curr->prev;
	while (ft_u8_is_alnum(curr->prev->charac[0]) && !curr->prev->is_prompt)
		curr = curr->prev;
	return (curr);
}

static t_char	*go_back_one_word(t_char *curr)
{
	while (!ft_u8_is_alnum(curr->charac[0]) && !curr->prev->is_prompt)
		curr = curr->prev;
	while (ft_u8_is_alnum(curr->prev->charac[0]) && !curr->prev->is_prompt)
		curr = curr->prev;
	return (curr);
}

t_char			*get_to_right_position(t_char *curr)
{
	int i;

	i = is_there_word_after(curr);
	if (i == 0)
		curr = go_back_two_words(curr);
	else
		curr = go_back_one_word(curr);
	return (curr);
}
