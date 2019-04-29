/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transpose_conditions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:08:18 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/02 18:20:30 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int		count_words(t_char *curr)
{
	int count;
	int t;

	count = 0;
	t = 0;
	while (curr->prev->is_prompt == 0)
		curr = curr->prev;
	while (curr)
	{
		if (ft_u8_is_alnum(curr->charac[0]) && t == 0)
		{
			t = 1;
			count++;
		}
		if (!ft_u8_is_alnum(curr->charac[0]))
			t = 0;
		curr = curr->next;
	}
	return (count);
}

static int		is_first_word(t_char *curr)
{
	if (curr->prev->is_prompt)
		return (1);
	if ((curr->next && !ft_u8_is_alnum(curr->next->charac[0]))
		|| !ft_u8_is_alnum(curr->charac[0]))
		return (0);
	while (curr->prev->is_prompt == 0 && ft_u8_is_alnum(curr->prev->charac[0]))
		curr = curr->prev;
	if (curr->prev->is_prompt)
		return (1);
	return (0);
}

int				transpose_word_conditions(t_char *curr)
{
	int nb;

	if (curr->is_prompt == 1 && !curr->next)
		return (0);
	if ((nb = count_words(curr)) == 0 || nb == 1)
		return (0);
	if (is_first_word(curr) == 1)
		return (0);
	return (1);
}
