/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:47:26 by emartine          #+#    #+#             */
/*   Updated: 2017/11/08 14:47:28 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strnlen(const char *str, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		if (str[i] == '\0')
			return (i);
		i++;
	}
	return (size);
}
