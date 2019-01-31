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
#include "hashmap_internal.h"

/*void	free_current(t_hashmap *hashmap, t_hashmap_key *current)
{
	if (current >= hashmap->array
			&& current <= hashmap->array[hashmap->arraysize - 1])
	{
		free(
	}
}*/

int		hashmap_set(t_hashmap *hashmap,
		uint8_t *key, size_t keysize,
		uint8_t *value, size_t valuesize)
{
	/*t_hashmap_key	*current;
	uint8_t			*keycopy;
	uint8_t			*valuecopy;

	// TODO check if key already set
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
	{
	}
	current->keysize = keysize;
	current->valuesize = valuesize;
	current->next = NULL;*/
	(void)hashmap;
	(void)key;
	(void)keysize;
	(void)value;
	(void)valuesize;
	return (-1);
}
