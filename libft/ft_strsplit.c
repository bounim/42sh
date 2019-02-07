/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 08:03:23 by schakor           #+#    #+#             */
/*   Updated: 2018/10/04 15:21:06 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	ft_len_words(char const *s, char c, size_t i)
{
	size_t	start;

	start = i;
	while (s[i] != c && s[i])
		++i;
	return (i - start);
}

static size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	state;
	size_t	nw;

	nw = 0;
	state = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			state = 0;
		else if (state == 0)
		{
			state = 1;
			nw += 1;
		}
		++i;
	}
	return (nw);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	size_t	len;
	size_t	ind[3];

	if (!s || (!(tab = (char **)malloc(sizeof(*tab) * (ft_count_words(s, c) +
							1)))))
		return (NULL);
	ind[0] = 0;
	ind[2] = 0;
	while (ind[0] < ft_count_words(s, c))
	{
		ind[1] = 0;
		while (s[ind[2]] == c && s[ind[2]])
			++ind[2];
		len = ft_len_words(s, c, ind[2]);
		if (!(tab[ind[0]] = (char *)malloc(sizeof(**tab) * (len + 1))))
			return (0);
		while (s[ind[2]] != c && s[ind[2]])
			tab[ind[0]][ind[1]++] = s[ind[2]++];
		tab[ind[0]++][ind[1]] = '\0';
	}
	tab[ind[0]] = 0;
	return (tab);
}
