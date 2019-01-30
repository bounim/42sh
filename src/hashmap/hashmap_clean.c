/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 16:17:23 by emartine          #+#    #+#             */
/*   Updated: 2019/01/30 16:17:25 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap_internal.h"

void	hashmap_clean(t_hashmap *hashmap)
{
	size_t	i;

	i = 0;
	while (i < hashmap->arraysize)
	{
		hashmap_clean_key(&hashmap->array[i]);
		i++;
	}
	free(hashmap->array);
}
