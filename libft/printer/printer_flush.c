/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_flush.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 15:16:25 by emartine          #+#    #+#             */
/*   Updated: 2019/03/06 15:59:46 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "printer.h"

void	printer_flush(t_printer *handle)
{
	size_t	i;
	ssize_t	r;

	if (handle->length > 0)
	{
		i = 0;
		while (i < handle->length)
		{
			r = write(handle->fd, handle->buffer + i, handle->length - i);
			if (r <= 0)
			{
				handle->length = 0;
				break ;
			}
			i += r;
		}
		handle->length = 0;
	}
}
