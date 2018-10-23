/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_numeric_length.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 19:21:02 by emartine          #+#    #+#             */
/*   Updated: 2018/03/08 19:21:03 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printer.h"

size_t	printer_int_length(int nbr)
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

size_t	printer_long_length(long nbr)
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

size_t	printer_uint_length(unsigned int nbr)
{
	size_t	length;

	length = 1;
	while (nbr > 9)
	{
		length++;
		nbr /= 10;
	}
	return (length);
}

size_t	printer_ulong_length(unsigned long nbr)
{
	size_t	length;

	length = 1;
	while (nbr > 9)
	{
		length++;
		nbr /= 10;
	}
	return (length);
}
