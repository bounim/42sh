/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstart.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 21:39:24 by emartine          #+#    #+#             */
/*   Updated: 2019/05/03 21:39:25 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strstart(char *haystack, char *needle)
{
	size_t	i;

	i = 0;
	while (haystack[i])
	{
		if (!needle[i])
			return (1);
		i++;
	}
	if (!needle[i])
		return (1);
	return (0);
}
