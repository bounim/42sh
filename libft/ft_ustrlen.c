/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ustrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 16:45:45 by emartine          #+#    #+#             */
/*   Updated: 2019/02/20 16:45:46 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_ustrlen(const uint8_t *ustr)
{
	uint8_t *ptr;

	ptr = (uint8_t *)ustr;
	while (*ptr)
		ptr++;
	return (ptr - ustr);
}
