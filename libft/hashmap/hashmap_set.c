/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 16:33:43 by emartine          #+#    #+#             */
/*   Updated: 2019/03/06 15:59:46 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "hashmap_internal.h"

static int	copy_keyvalue(t_hashmap_key *current, t_hashmap_key *kv)
{
	if (NULL == (current->value = malloc(kv->valuesize)))
		return (-1);
	if (NULL == (current->key = malloc(kv->keysize)))
	{
		free(current->value);
		return (-1);
	}
	ft_memmove(current->key, kv->key, kv->keysize);
	ft_memmove(current->value, kv->value, kv->valuesize);
	current->keysize = kv->keysize;
	current->valuesize = kv->valuesize;
	return (0);
}

static int	set_list(t_hashmap_key *current, t_hashmap_key *kv)
{
	while (1)
	{
		if (kv->keysize == current->keysize
				&& ft_memcmp(kv->key, current->key, kv->keysize) == 0)
		{
			free(current->value);
			if (NULL == (current->value = malloc(kv->valuesize)))
				return (-1);
			ft_memmove(current->value, kv->value, kv->valuesize);
			current->valuesize = kv->valuesize;
			return (0);
		}
		if (!current->next)
		{
			if (NULL == (current->next = malloc(sizeof(*current->next))))
				return (-1);
			ft_memset(current->next, 0, sizeof(*current->next));
			return (copy_keyvalue(current->next, kv));
		}
		current = current->next;
	}
	return (-1);
}

int			hashmap_set(t_hashmap *hashmap, t_hashmap_key *kv)
{
	t_hashmap_key	*current;

	current = &hashmap->array[hashmap->hash(hashmap, kv->key, kv->keysize)];
	if (current->key)
		return (set_list(current, kv));
	return (copy_keyvalue(current, kv));
}
