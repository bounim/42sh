/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_exclaim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:46:49 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/13 19:24:05 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static char		*replace_exclaim_word(t_history *history, char *word)
{
	int			i;

	i = 1;
	while (history)
	{
		if (word[i] == history->buf[0])
		{
			if (ft_strequ(word, (char *)history->buf))
				return ((char *)history->buf);
		}
		history = history->bfr;
	}
	return (NULL);
}

static char		*replace_exclaim_nb(t_history *history, char *word)
{
	int		nb;
	size_t	stock;

	nb = 0;
	stock = ft_strlen(word);
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
	return ((char *)history->buf);
}

static char		*replace_exclaim_neg(t_history *history, char *word)
{
	int		nb;
	size_t	stock;

	nb = 0;
	word++;
	stock = ft_strlen(word);
	while (stock--)
	{
		nb *= 10;
		nb += (int)(word++) - 48;
	}
	if (g_shell.hist.history_size > nb)
		return (NULL);
	while (--nb)
		history = history->bfr;
	return ((char *)history->buf);
}

static char		*find_exclaim(char *word, t_history *hist)
{
	if (!word || !word[1])
		return (NULL);
	if (word[1] == '!')
		return ((char *)hist->bfr->buf);
	else if (word[1] >= 0 && word[1] <= 9)
		return (replace_exclaim_nb(hist, word++));
	else if (word[0] == '-')
		return (replace_exclaim_neg(hist, word++));
	else
		return (replace_exclaim_word(hist, word++));
}

static int		concat_exclaim(char *line, int i)
{
	int	j;
	
	j = i + 1;
	if (!line[j])
		return (0);
	else if (line[j] == '!')
		j++;
	else if (ft_isalpha(line[j]))
		while (ft_isalnum(line[j]))
			j++;
	else if (ft_isdigit(line[j]))
		while (ft_isdigit(line[j]))
			j++;
	return (j - 1);
}

char				*replace_exclaim(char *line, t_history *hist)
{
	int		i;
	int		j;
	char	*concat;
	char	*bfr;
	char	*next;
	char	*tmp;

	while ((i = ft_strichr(line, '!')))
	{
		if ((j = concat_exclaim(line, i)) == 0)
			return (NULL);
		if (!(concat = ft_strsub(line, i, j - i + 1)) || !(bfr = ft_strsub(line, 0, i)) ||
			!(tmp = find_exclaim(concat, hist)) || !(next = ft_strsub(line, j, ft_strlen(line))))
		{
			ft_putstr_fd("event not found: ", 2);
			ft_putstr_fd(line + i + 1, 2);
			write(2, "\n", 1);
			return (NULL);
		}
		ft_strdel(&line);
		line = ft_strfjoin(bfr, tmp, 2);
		line = ft_strfjoin(line, next, 2);
	}
	return (line);
}
