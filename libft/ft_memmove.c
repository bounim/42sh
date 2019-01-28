/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 18:44:07 by emartine          #+#    #+#             */
/*   Updated: 2017/11/07 18:44:09 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"

void				*ft_memmove(void *dst, const void *src, size_t len)
{
	char			*d1;
	const char		*s1;
	uint64_t		*d8;
	const uint64_t	*s8;
	int				s;

	if (src == dst || len == 0)
		return (dst);
	s = src < dst ? 1 : 0;
	d8 = (uint64_t *)((char *)dst + len * s);
	s8 = (uint64_t *)((char *)src + len * s);
	while (len >= 8)
	{
		s ? (*(--d8) = *(--s8))
			: (*d8++ = *s8++);
		len -= 8;
	}
	d1 = (char *)d8;
	s1 = (char *)s8;
	while (len--)
		s ? (*(--d1) = *(--s1))
			: (*d1++ = *s1++);
	return (dst);
}
