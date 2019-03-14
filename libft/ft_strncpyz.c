/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpyz.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 19:49:20 by emartine          #+#    #+#             */
/*   Updated: 2019/03/06 15:59:46 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpyz(char *dest, const char *src, size_t n)
{
	size_t	l;

	if (n == 0)
		return (dest);
	l = ft_strnlen(src, n - 1);
	ft_memmove(dest, src, l);
	ft_memset(dest + l, 0, n - l);
	return (dest);
}
