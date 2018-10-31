/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 18:20:43 by emartine          #+#    #+#             */
/*   Updated: 2017/11/07 18:20:45 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"

void				*ft_memset(void *b, int c, size_t len)
{
	uint64_t	c8;
	uint64_t	*b8;
	char		*b1;

	c8 = 0x0101010101010101 * (unsigned char)c;
	b8 = b;
	while (len > 7)
	{
		*b8++ = c8;
		len -= 8;
	}
	b1 = (char *)b8;
	while (len--)
		*b1++ = c;
	return (b);
}
