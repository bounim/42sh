/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_ulong.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 16:36:06 by emartine          #+#    #+#             */
/*   Updated: 2018/03/07 16:36:07 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printer.h"

void	printer_ulong(t_printer_handle *handle, unsigned long l)
{
	char	buffer[20];
	size_t	length;
	size_t	i;

	length = printer_ulong_length(l);
	if (length > 20)
		return ;
	i = length;
	while (i--)
	{
		buffer[i] = '0' + l % 10;
		l /= 10;
	}
	printer_bin(handle, buffer, length);
}
