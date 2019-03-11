/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_clean_key.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 16:10:59 by emartine          #+#    #+#             */
/*   Updated: 2019/03/06 15:59:46 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "hashmap_internal.h"

void	hashmap_clean_key(t_hashmap_key *key)
{
	t_hashmap_key *next;

	if (!key)
		return ;
	free(key->key);
	free(key->value);
	next = key->next;
	while (next)
	{
		key = next;
		next = key->next;
		free(key->key);
		free(key->value);
		free(key);
	}
}
