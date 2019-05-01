/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 14:50:30 by emartine          #+#    #+#             */
/*   Updated: 2019/05/01 14:50:32 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char		*ft_arrjoin_copy(char **arr, size_t *strl, size_t rl)
{
	char	*r;
	size_t	i;

	if (NULL == (r = malloc(rl)))
	{
		free(strl);
		return (NULL);
	}
	i = 0;
	while (*arr)
	{
		ft_memmove(r + i, *arr, *strl);
		r[i + *strl] = arr[i + 1] ? ' ' : '\0';
		i += *strl + 1;
		arr++;
		strl++;
	}
	return (r);
}

char			*ft_arrjoin(char **arr)
{
	size_t	i;
	size_t	arrl;
	size_t	*strl;
	size_t	rl;

	arrl = ft_arrlen(arr);
	if (NULL == (strl = malloc(arrl * sizeof(*strl))))
		return (NULL);
	i = 0;
	rl = 0;
	while (arr[i])
	{
		strl[i] = ft_strlen(arr[i]);
		rl += strl[i] + 1;
		i++;
	}
	return (ft_arrjoin_copy(arr, strl, rl));
}
