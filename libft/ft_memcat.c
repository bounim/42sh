/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:49:35 by emartine          #+#    #+#             */
/*   Updated: 2019/02/01 17:49:36 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include "libft.h"

void	*ft_memcat(const void *a, size_t an, const void *b, size_t bn)
{
	void	*r;

	if (NULL == (r = malloc(an + bn)))
		return (NULL);
	ft_memmove(r, a, an);
	ft_memmove(r + an, b, bn);
	return (r);
}
