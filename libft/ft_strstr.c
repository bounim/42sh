/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 10:55:06 by aguillot          #+#    #+#             */
/*   Updated: 2017/12/01 15:01:40 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strstr(const char *h, const char *n)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i <= ft_strlen(h))
	{
		j = 0;
		while (h[i + j] == n[j] && n[j])
			j++;
		if (!n[j])
			return ((char*)(h + i));
		i++;
	}
	return (0);
}
