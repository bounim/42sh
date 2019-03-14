/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 17:03:50 by emartine          #+#    #+#             */
/*   Updated: 2019/03/06 15:59:46 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "hashmap_internal.h"

static int	unset_key(t_hashmap_key *current)
{
	free(current->key);
	free(current->value);
	if (current->next)
	{
		current->key = current->next->key;
		current->keysize = current->next->keysize;
		current->value = current->next->value;
		current->valuesize = current->next->valuesize;
		current->next = current->next->next;
		return (0);
	}
	return (1);
}

static int	unset_list(t_hashmap_key *current,
		uint8_t *key, size_t keysize)
{
	while (current)
	{
		if (keysize == current->keysize
				&& ft_memcmp(key, current->key, keysize) == 0)
		{
			if (unset_key(current))
				free(current);
			return (0);
		}
		current = current->next;
	}
	return (-1);
}

int			hashmap_unset(t_hashmap *hashmap,
		uint8_t *key, size_t keysize)
{
	t_hashmap_key	*current;

	current = &hashmap->array[hashmap->hash(hashmap, key, keysize)];
	if (!current->key)
		return (-1);
	if (keysize == current->keysize
			&& ft_memcmp(key, current->key, keysize) == 0)
	{
		if (unset_key(current))
			current->key = NULL;
		return (0);
	}
	return (unset_list(current->next, key, keysize));
}
