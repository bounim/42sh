/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 14:14:50 by emartine          #+#    #+#             */
/*   Updated: 2019/03/06 15:59:46 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTER_H
# define PRINTER_H

# include <limits.h>
# include <stddef.h>
# include <stdint.h>

# define PRINTER_BUFFER_SIZE PIPE_BUF

typedef struct	s_printer
{
	int			fd;
	char		buffer[PRINTER_BUFFER_SIZE + 1];
	size_t		length;
}				t_printer;

/*
** initialize pointed struct
*/
void			printer_init(t_printer *handle, int fd);
/*
** flush buffer (required to ensure output)
*/
void			printer_flush(t_printer *handle);

/*
** functions used to print and/or add to buffer the following types
*/
void			printer_str(t_printer *handle, const char *str);
void			printer_ustr(t_printer *handle, const uint8_t *ustr);
void			printer_bin(t_printer *handle, const uint8_t *bin,
		size_t size);
void			printer_endl(t_printer *handle);
void			printer_int(t_printer *handle, int n);
void			printer_long(t_printer *handle, long l);
void			printer_ulong(t_printer *handle, unsigned long l);
void			printer_char(t_printer *handle, char ch);

#endif
