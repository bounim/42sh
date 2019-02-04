/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 16:33:43 by emartine          #+#    #+#             */
/*   Updated: 2019/01/30 16:33:45 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "hashmap_internal.h"

static int	copy_keyvalue(t_hashmap_key *current,
		uint8_t *key, size_t keysize,
		uint8_t *value, size_t valuesize)
{
	if (NULL == (current->value = malloc(valuesize)))
		return (-1);
	if (NULL == (current->key = malloc(keysize)))
	{
		free(current->value);
		return (-1);
	}
	ft_memmove(current->key, key, keysize);
	ft_memmove(current->value, value, valuesize);
	current->keysize = keysize;
	current->valuesize = valuesize;
	return (0);
}

static int	set_list(t_hashmap_key *current,
		uint8_t *key, size_t keysize,
		uint8_t *value, size_t valuesize)
{
	while (1)
	{
		if (keysize == current->keysize
				&& ft_memcmp(key, current->key, keysize) == 0)
		{
			free(current->value);
			if (NULL == (current->value = malloc(valuesize)))
				return (-1);
			ft_memmove(current->value, value, valuesize);
			current->valuesize = valuesize;
			return (0);
		}
		if (!current->next)
		{
			if (NULL == (current->next = malloc(sizeof(*current->next))))
				return (-1);
			return (copy_keyvalue(current->next, key, keysize,
						value, valuesize));
		}
		current = current->next;
	}
	return (-1);
}

int			hashmap_set(t_hashmap *hashmap,
		uint8_t *key, size_t keysize,
		uint8_t *value, size_t valuesize)
{
	t_hashmap_key	*current;

	current = &hashmap->array[hashmap->hash(hashmap, key, keysize)];
	if (current->key)
		return (set_list(current, key, keysize, value, valuesize));
	return (copy_keyvalue(current, key, keysize, value, valuesize));
}
