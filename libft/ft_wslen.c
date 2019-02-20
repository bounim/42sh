/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wslen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <schakor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 09:52:35 by schakor           #+#    #+#             */
/*   Updated: 2019/02/06 10:17:58 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_wslen(char *str)
{
	size_t	i;
	size_t	ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if ((str[i] & 0x80) == 0x00)
			i++;
		else if ((str[i] & 0xc0) == 0xc0)
			i += 2;
		else if ((str[i] & 0xe0) == 0xe0)
			i += 3;
		else if ((str[i] & 0xf0) == 0xf0)
			i += 4;
		else if ((str[i] & 0xf8) == 0xf8)
			i += 5;
		else if ((str[i] & 0xfc) == 0xfc)
			i += 6;
		ret++;
	}
	return (ret);
}
