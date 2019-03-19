/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_carac_nb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 18:20:50 by aguillot          #+#    #+#             */
/*   Updated: 2019/03/09 13:25:37 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t		ft_carac_size(uint8_t *buf, size_t ulen)
{
	if (ulen == 0)
		return (0);
	if (*buf <= 127)
		return (1);
	if (*buf >= 192 && *buf <= 223 && 2 <= ulen)
		return (2);
	if (*buf >= 224 && *buf <= 239 && 3 <= ulen)
		return (3);
	if (*buf >= 240 && *buf <= 247 && 4 <= ulen)
		return (4);
	if (*buf >= 248 && *buf <= 251 && 5 <= ulen)
		return (5);
	if (*buf >= 252 && *buf <= 253 && 6 <= ulen)
		return (6);
	return (-1);
}

ssize_t		ft_carac_nb(uint8_t *str, size_t ulen)
{
	size_t	i;
	ssize_t	r;
	ssize_t	size;

	if (str == NULL)
		return (0);
	i = 0;
	size = 0;
	while (i < ulen)
	{
		if ((r = ft_carac_size(str + i, ulen - i)) == -1)
			return (-1);
		size++;
		i += r;
	}
	return (size);
}
