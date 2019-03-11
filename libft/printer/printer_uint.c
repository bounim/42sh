/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_uint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 16:36:12 by emartine          #+#    #+#             */
/*   Updated: 2019/03/06 15:59:46 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printer.h"

void	printer_uint(t_printer_handle *handle, unsigned int n)
{
	char	buffer[10];
	size_t	length;
	size_t	i;

	length = printer_uint_length(n);
	if (length > 10)
		return ;
	i = length;
	while (i--)
	{
		buffer[i] = '0' + n % 10;
		n /= 10;
	}
	printer_bin(handle, buffer, length);
}
