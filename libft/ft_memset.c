/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 18:20:43 by emartine          #+#    #+#             */
/*   Updated: 2017/11/07 18:20:45 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*dst;

	dst = (unsigned char *)b;
	while (dst < (unsigned char *)b + len)
		*(dst++) = (unsigned char)c;
	return (b);
}
