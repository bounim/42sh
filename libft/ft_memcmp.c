/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 15:46:35 by emartine          #+#    #+#             */
/*   Updated: 2019/03/06 15:59:46 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"

int		ft_memcmp(void *a, const void *b, size_t len)
{
	uint64_t	*a8;
	uint64_t	*b8;
	uint8_t		*a1;
	uint8_t		*b1;

	a8 = (uint64_t *)a;
	b8 = (uint64_t *)b;
	while (len > 7 && *a8 == *b8)
	{
		a8++;
		b8++;
		len -= 8;
	}
	a1 = (uint8_t *)a8;
	b1 = (uint8_t *)b8;
	while (len > 0 && *a1 == *b1)
	{
		a1++;
		b1++;
		len--;
	}
	if (len == 0)
		return (0);
	return (*a1 - *b1);
}
