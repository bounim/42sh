/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exclaim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:17:59 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/02 18:10:47 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static size_t	my_memcmp(uint8_t *s1, t_history *history, size_t size)
{
	size_t k;
	size_t i;

	i = 0;
	k = 0;
	while (history->buf[k] && i < size)
	{
		if (s1[i] != history->buf[k])
			return (0);
		k++;
		i++;
	}
	if (!(history->buf[k]))
		return (1);
	return (0);
}

static t_history	*replace_exclaim_word(t_history *history, uint8_t *word, int size)
{
	int			i;

	i = 1;
	while (history)
	{
		if (word[i] == history->buf[0])
		{
			if (my_memcmp(word, history, size))
				return (history);
		}
		history = history->bfr;
	}
	return (NULL);
}

static t_history	*replace_exclaim_nb(t_history *history, uint8_t *word, int size)
{
	size_t	nb;
	size_t	stock;

	nb = 0;
	stock = size;
	while (stock--)
	{
		nb *= 10;
		nb += (int)(word++) - 48;
	}	
	// if (history_size > nb)
	// return (NULL);
	while (history->bfr)
		history = history->bfr;
	while (--nb)
		history = history->next;
	return (history);
}

static t_history	*replace_exclaim_neg(t_history *history, uint8_t *word, int size)
{
	size_t	nb;
	size_t	stock;

	nb = 0;
	word++;
	stock = size;
	while (stock--)
	{
		nb *= 10;
		nb += (int)(word++) - 48;
	}
	// if (history_size > nb)
	// return (NULL);
	while (--nb)
		history = history->bfr;
	return (history);
}

t_history	*built_exclaim(uint8_t *word, int size, t_history *head)
{
	if (!word[1])
		return (NULL);
	if (word[1] == '!')
		return (head->bfr);
	else if (word[1] >= 0 && word[1] <= 9)
		return (replace_exclaim_nb(head, word++, size--));
	else if (word[0] == '-')
		return (replace_exclaim_neg(head, word++, (size -= 2)));
	else
		return (replace_exclaim_word(head, word++, size--));
}
