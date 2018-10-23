/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 16:17:27 by emartine          #+#    #+#             */
/*   Updated: 2018/03/07 16:17:29 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printer.h"

void	printer_long(t_printer_handle *handle, long l)
{
	char	buffer[11];
	char	*bufferptr;
	size_t	length;
	size_t	i;

	length = printer_long_length(l);
	if (length > 11)
		return ;
	i = length;
	bufferptr = (char *)buffer;
	if (l < 0)
	{
		*(bufferptr++) = '-';
		i--;
	}
	while (i--)
	{
		bufferptr[i] = '0' + (l < 0 ? -(l % 10) : l % 10);
		l /= 10;
	}
	printer_bin(handle, buffer, length);
}
