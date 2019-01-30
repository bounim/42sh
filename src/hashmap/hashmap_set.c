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

#include "hashmap_internal.h"

int		hashmap_set(t_hashmap *hashmap,
		uint8_t *key, size_t keysize,
		uint8_t *value, size_t valuesize);
{
	t_hashmap_key *current;
	uint8_t	*keycopy;
	uint8_t	*valuecopy;

	current = &hashmap->array[hashmap->hash(hashmap, key, keysize)];
	if (current->key)
	{
		while (current->next != NULL)
			current = current->next;
		if (NULL == (current->next = malloc(sizeof(*current->next))))
			return (-1);
		current = current->next; // must diff malloc
	}
	if (NULL == (current->key = malloc(keysize)))
	current->keysize = keysize;
	current->valuesize = valuesize;
	current->next = NULL;
	return (-1);
}
