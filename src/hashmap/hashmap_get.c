/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 17:14:29 by emartine          #+#    #+#             */
/*   Updated: 2019/01/30 17:14:30 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hashmap_internal.h"

t_hashmap_key	*hashmap_get(t_hashmap *hashmap, uint8_t *key, size_t keysize)
{
	t_hashmap_key	*current;

	current = &hashmap->array[hashmap->hash(hashmap, key, keysize)];
	if (!current->key)
		return (NULL);
	if (!current->next)
		return (current);
	while (current)
	{
		if (current->keysize == keysize
				&& ft_memcmp(current->key, key, keysize) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
