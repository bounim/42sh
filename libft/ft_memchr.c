/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:36:49 by kberisha          #+#    #+#             */
/*   Updated: 2019/03/07 14:36:52 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memchr(const void *s, size_t size, int c)
{
	size_t	i;
    uint8_t *s8;

	i = 0;
    s8 = (uint8_t *)s;
	while (i < size)
	{
		if (s8[i] == c)
			return (s8 + i);
		i++;
	}
	return (NULL);
}
