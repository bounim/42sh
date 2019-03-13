/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 15:33:18 by emartine          #+#    #+#             */
/*   Updated: 2019/03/06 15:59:46 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printer.h"

void	printer_bin(t_printer *handle, const uint8_t *bin, size_t size)
{
	size_t	diff;

	if (!bin)
		return ;
	while (size)
	{
		if (handle->length + size <= PRINTER_BUFFER_SIZE)
		{
			ft_memmove(handle->buffer + handle->length, bin, size);
			handle->length += size;
			size = 0;
			if (handle->length == PRINTER_BUFFER_SIZE)
				printer_flush(handle);
		}
		else
		{
			diff = PRINTER_BUFFER_SIZE - handle->length;
			ft_memmove(handle->buffer + handle->length, bin, diff);
			handle->length += diff;
			bin += diff;
			size -= diff;
			printer_flush(handle);
		}
	}
}
