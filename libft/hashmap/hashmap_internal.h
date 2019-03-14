/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 16:07:57 by emartine          #+#    #+#             */
/*   Updated: 2019/03/06 15:59:46 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHMAP_INTERNAL_H
# define HASHMAP_INTERNAL_H

# include "hashmap.h"

/*
** free a key in hashmap->array and its children (linked list)
** must not free itself (array member)
*/

void	hashmap_clean_key(t_hashmap_key *key);

#endif
