/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_exclaim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:46:49 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/13 18:53:20 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"
/*
static t_history	*replace_exclaim_word(t_history *history, char *word)
{
	int			i;

	i = 1;
	while (history)
	{
		if (word[i] == history->buf[0])
		{
			if (ft_strequ(word, history))
				return (history);
		}
		history = history->bfr;
	}
	return (NULL);
}

static t_history	*replace_exclaim_nb(t_history *history, char *word)
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
	if (g_shell.hist.history_size > nb)
		return (NULL);
	while (history->bfr)
		history = history->bfr;
	while (--nb)
		history = history->next;
	return (history);
}

static t_history	*replace_exclaim_neg(t_history *history, char *word)
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
	if (g_shell.hist.history_size > nb)
		return (NULL);
	while (--nb)
		history = history->bfr;
	return (history);
}

static t_history	*find_exclaim(char *word, t_history *head)
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
*/
char				*replace_exclaim(char *line, t_history *hist);
