/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:21:23 by kberisha          #+#    #+#             */
/*   Updated: 2017/11/20 02:27:04 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	str = NULL;
	if (s)
	{
		if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
			return (NULL);
		i = start;
		while (i < (len + start) && s[i])
		{
			str[i - start] = s[i];
			i++;
		}
		str[len] = '\0';
	}
	return (str);
}
