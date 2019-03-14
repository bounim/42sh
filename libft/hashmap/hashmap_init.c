/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 16:33:33 by emartine          #+#    #+#             */
/*   Updated: 2019/03/06 15:59:46 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "hashmap_internal.h"

int							hashmap_init(t_hashmap *hashmap, size_t size,
		t_hashmap_func hash)
{
	if (NULL == (hashmap->array = malloc(size * sizeof(*hashmap->array))))
		return (-1);
	ft_memset(hashmap->array, 0, size * sizeof(*hashmap->array));
	hashmap->hash = hash;
	hashmap->arraysize = size;
	hashmap->length = 0;
	return (0);
}
