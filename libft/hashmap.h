/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 15:43:40 by emartine          #+#    #+#             */
/*   Updated: 2019/01/30 15:43:42 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHMAP_H
# define HASHMAP_H

# include <stddef.h>
# include <stdint.h>

typedef struct s_hashmap_key	t_hashmap_key;
typedef struct s_hashmap		t_hashmap;
typedef size_t					(*t_hashmap_func)(t_hashmap *hashmap,
		uint8_t *key, size_t keysize);

/*
** next: linked list for collisions
** key, keysize: binary key (copied)
** data, datasize: data (copied)
*/

struct							s_hashmap_key
{
	t_hashmap_key				*next;
	uint8_t						*key;
	size_t						keysize;
	void						*value;
	size_t						valuesize;
};

/*
** hash: function used to compute array index from a key
** !warning! it is assumed that the function always returns a valid index
** array, arraysize: array of saved keys, NULL when unused
** !warning! array elements are not pointers
** length: number of saved keys
*/

struct							s_hashmap
{
	t_hashmap_func				hash;
	t_hashmap_key				*array;
	size_t						arraysize;
	size_t						length;
};

/*
** hashmap: statically allocated
** size: size of array (hashmap->arraysize), assumed > 0
** array is memset to 0
** returns 0 on success, -1 if allocation failed
*/

int								hashmap_init(t_hashmap *hashmap, size_t size,
		t_hashmap_func hash);

/*
** free all keys and values
*/

void							hashmap_clean(t_hashmap *hashmap);

/*
** set key to value
** keysize: assumed > 0
** returns 0 on success, -1 if allocation failed
*/

int								hashmap_set(t_hashmap *hashmap,
		uint8_t *key, size_t keysize,
		uint8_t *value, size_t valuesize);

/*
** returns NULL if key not found, or the key structure
*/

t_hashmap_key					*hashmap_get(t_hashmap *hashmap,
		uint8_t *key, size_t keysize);

#endif
