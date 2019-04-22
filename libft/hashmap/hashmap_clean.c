/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 16:17:23 by emartine          #+#    #+#             */
/*   Updated: 2019/03/06 15:59:46 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "hashmap_internal.h"

void	hashmap_clean(t_hashmap *hashmap)
{
	size_t	i;

	if (!hashmap->array)
		return ;
	i = 0;
	while (i < hashmap->arraysize)
	{
		hashmap_clean_key(&hashmap->array[i]);
		i++;
	}
	free(hashmap->array);
}
