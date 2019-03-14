/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 15:26:04 by schakor           #+#    #+#             */
/*   Updated: 2019/03/06 15:59:46 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t n)
{
	char	*ret;
	size_t	i;

	if (s != NULL)
	{
		if (!(ret = (char *)malloc(sizeof(*ret) * (n + 1))))
			return (NULL);
		i = 0;
		while (n--)
		{
			ret[i] = s[start];
			++i;
			++start;
		}
		ret[i] = '\0';
		return (ret);
	}
	return (NULL);
}
