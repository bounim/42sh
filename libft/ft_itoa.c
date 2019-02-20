/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 14:18:31 by schakor           #+#    #+#             */
/*   Updated: 2017/11/30 15:50:59 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char			*ft_itoa(int n)
{
	char	*ret;
	int		tmp;
	int		len;

	tmp = n;
	len = 1;
	if (n < 0)
		len += 1;
	while ((tmp /= 10))
		len += 1;
	tmp = n;
	if (!(ret = (char *)malloc(sizeof(*ret) * (len + 1))))
		return (NULL);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		n = -n;
	ret[len--] = '\0';
	while (len >= 0)
	{
		ret[len--] = n % 10 + '0';
		n /= 10;
	}
	ret[0] = (tmp < 0) ? '-' : ret[0];
	return (ret);
}
