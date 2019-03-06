/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 16:17:22 by emartine          #+#    #+#             */
/*   Updated: 2019/03/06 15:59:46 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printer.h"

static size_t	printer_int_length(int nbr)
{
	size_t	length;

	length = nbr < 0 ? 2 : 1;
	while (nbr < -9 || nbr > 9)
	{
		length++;
		nbr /= 10;
	}
	return (length);
}

void			printer_int(t_printer *handle, int n)
{
	uint8_t	buffer[6];
	uint8_t	*bufferptr;
	size_t	length;
	size_t	i;

	length = printer_int_length(n);
	if (length > 6)
		return ;
	i = length;
	bufferptr = (uint8_t *)buffer;
	if (n < 0)
	{
		*(bufferptr++) = '-';
		i--;
	}
	while (i--)
	{
		bufferptr[i] = '0' + (n < 0 ? -(n % 10) : n % 10);
		n /= 10;
	}
	printer_bin(handle, buffer, length);
}
