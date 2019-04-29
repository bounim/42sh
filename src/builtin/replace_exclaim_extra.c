/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_exclaim_extra.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 17:36:57 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/24 15:15:19 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static char		*replace_exclaim_word(t_history *history, char *word)
{
	word++;
	while (history)
	{
		if (ft_strnequ(word, (char *)history->buf, ft_strlen(word)))
			return ((char *)history->buf);
		history = history->bfr;
	}
	return (NULL);
}

static char		*replace_exclaim_nb(t_history *history, char *word)
{
	int		nb;
	size_t	stock;

	nb = 0;
	word++;
	stock = ft_strlen(word);
	while (stock--)
	{
		nb *= 10;
		nb += (int)(*word) - 48;
		word++;
	}
	if (g_shell.hist.history_size < nb || nb == 0)
		return (NULL);
	while (history->bfr)
		history = history->bfr;
	while (--nb)
		history = history->next;
	return ((char *)history->buf);
}

static char		*replace_exclaim_neg(t_history *history, char *word)
{
	int		nb;
	size_t	stock;

	nb = 0;
	word += 2;
	stock = ft_strlen(word);
	while (stock--)
	{
		nb *= 10;
		nb += (int)(*word) - 48;
		word++;
	}
	if (g_shell.hist.history_size < nb || nb == 0)
		return (NULL);
	while (--nb)
		history = history->bfr;
	return ((char *)history->buf);
}

char			*find_exclaim(char *word, t_history *hist)
{
	if (!word && (!word[0] || !word[1]))
		return (NULL);
	if (g_shell.hist.history_size <= 0)
		return (NULL);
	if (word[1] == '!')
		return ((char *)hist->buf);
	else if (ft_isdigit(word[1]))
		return (replace_exclaim_nb(hist, word++));
	else if (word[1] == '-')
		return (replace_exclaim_neg(hist, word++));
	else
		return (replace_exclaim_word(hist, word++));
}
