/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 15:50:07 by emartine          #+#    #+#             */
/*   Updated: 2018/03/07 15:50:09 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printer.h"

void	printer_str(t_printer_handle *handle, char *str)
{
	if (!str)
		return ;
	printer_bin(handle, str, ft_strlen(str));
}
