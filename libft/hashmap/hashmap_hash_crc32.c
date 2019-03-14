/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_hash_crc32.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 13:59:15 by emartine          #+#    #+#             */
/*   Updated: 2019/03/06 15:59:46 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap_internal.h"

static uint32_t	*crc_init(void)
{
	static uint32_t	table[256] = {0};
	uint32_t		rem;
	uint32_t		div;
	int				i;

	if (table[1])
		return (table);
	div = 0;
	while (div < 256)
	{
		rem = div << (8 * 3);
		i = 0;
		while (i < 8)
		{
			if (rem & (1 << 31))
				rem = (rem << 1) ^ 0x04C11DB7UL;
			else
				rem <<= 1;
			i++;
		}
		table[div] = rem;
		div++;
	}
	return (table);
}

size_t			hashmap_hash_crc32(t_hashmap *hashmap,
		uint8_t *key, size_t keysize)
{
	uint32_t	*table;
	size_t		i;
	uint32_t	rem;

	table = crc_init();
	i = 0;
	rem = 0;
	while (i < keysize)
		rem = table[key[i++] ^ rem >> (8 * 3)] ^ (rem << 8);
	return (rem % hashmap->arraysize);
}
