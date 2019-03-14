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
	word++;
	stock = ft_strlen(word);
	while (stock--)
	{
		nb *= 10;
		nb += (int)(*word) - 48;
		word++;
	}
//	printf("ici\n");
//	printf("size = %d | nb = %d\n", g_shell.hist.history_size, nb);
	if (g_shell.hist.history_size < nb)
		return (NULL);
//	printf("ici\n");
	while (history->bfr)
		history = history->bfr;
//	printf("tjr la\n");
	while (--nb)
		history = history->next;
//	printf("history = %s\n", history->buf);
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
	if (g_shell.hist.history_size < nb)
		return (NULL);
	while (--nb)
		history = history->bfr;
	return ((char *)history->buf);
}

static char		*find_exclaim(char *word, t_history *hist)
{
//	printf("word=%s\n", word);
	if (!word && (!word[0] || !word[1]))
		return (NULL);
//	printf("%c\n",word[1]);
	if (word[1] == '!')
		return ((char *)hist->bfr->buf);
	else if (ft_isdigit(word[1]))
		return (replace_exclaim_nb(hist, word++));
	else if (word[1] == '-')
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
	//	printf("%c %c\n", line[i], line[j]);
		if (!(concat = ft_strsub(line, i, j - i + 1)) || !(bfr = ft_strsub(line, 0, i)) ||
			!(tmp = find_exclaim(concat, hist)) || !(next = ft_strsub(line, j + 1, ft_strlen(line) - j)))
		{
		//	printf("%s | %s | %s | %s\n", concat, bfr, tmp, next);
			ft_putstr_fd("event not found: ", 2);
			ft_putstr_fd(line + i + 1, 2);
			write(2, "\n", 1);
			return (NULL);
		}
		ft_strdel(&line);
		line = ft_strfjoin(bfr, tmp, 2);
		line = ft_strfjoin(line, next, 2);
		printf("line = %s\n", line);
	}
	return (line);
}
