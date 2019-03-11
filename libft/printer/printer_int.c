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

void	printer_int(t_printer_handle *handle, int n)
{
	char	buffer[6];
	char	*bufferptr;
	size_t	length;
	size_t	i;

	length = printer_int_length(n);
	if (length > 6)
		return ;
	i = length;
	bufferptr = (char *)buffer;
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
