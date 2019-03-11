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
# include <stdlib.h>

# define PRINTER_BUFFER_SIZE 4096

typedef struct	s_printer_handle
{
	int			fd;
	char		buffer[PRINTER_BUFFER_SIZE + 1];
	size_t		length;
}				t_printer_handle;

/*
** initialize pointed struct
*/
void			printer_init(t_printer_handle *handle, int fd);
/*
** flush buffer (required to ensure output)
*/
void			printer_flush(t_printer_handle *handle);

/*
** functions used to print and/or add to buffer the following types
*/
void			printer_str(t_printer_handle *handle, char *str);
void			printer_bin(t_printer_handle *handle, char *bin, size_t size);
void			printer_int(t_printer_handle *handle, int n);
void			printer_uint(t_printer_handle *handle, unsigned int n);
void			printer_long(t_printer_handle *handle, long l);
void			printer_ulong(t_printer_handle *handle, unsigned long l);
void			printer_char(t_printer_handle *handle, char ch);
void			printer_endl(t_printer_handle *handle);

/*
** internal functions
*/

/*
** numeric types length
*/
size_t			printer_int_length(int nbr);
size_t			printer_uint_length(unsigned int nbr);
size_t			printer_long_length(long nbr);
size_t			printer_ulong_length(unsigned long nbr);

#endif
