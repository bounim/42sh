/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:52:35 by schakor           #+#    #+#             */
/*   Updated: 2019/03/26 14:53:01 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		ft_atoi(const char *s)
{
	int		ret;
	int		sign;

	if (!s)
		return (0);
	while (*s == ' ' || (*s >= '\t' && *s <= '\r'))
		++s;
	sign = 1;
	if (*s == '+')
		++s;
	else if (*s == '-')
	{
		++s;
		sign = -1;
	}
	ret = 0;
	while (*s >= '0' && *s <= '9')
	{
		ret = ret * 10 + *s - '0';
		++s;
	}
	return (ret * sign);
}
