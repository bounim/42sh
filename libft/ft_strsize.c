/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 16:45:52 by emartine          #+#    #+#             */
/*   Updated: 2019/02/20 16:45:53 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strsize(const char *str)
{
	char *ptr;

	ptr = (char *)str;
	while (*ptr)
		ptr++;
	return ((uint8_t *)ptr - (uint8_t *)str);
}
