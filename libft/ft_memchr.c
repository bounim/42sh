/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 20:01:02 by schakor           #+#    #+#             */
/*   Updated: 2018/04/06 10:34:48 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cptr;

	cptr = (unsigned char *)s;
	while (n--)
	{
		if (*cptr == (unsigned char)c)
			return ((void *)cptr);
		++cptr;
	}
	return (NULL);
}
