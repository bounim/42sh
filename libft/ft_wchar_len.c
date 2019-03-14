/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wchar_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 14:06:42 by aguillot          #+#    #+#             */
/*   Updated: 2019/02/01 14:49:25 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wchar_len(unsigned char *str)
{
	if (str)
	{
		if (str[0] >= 0 && str[0] <= 127)
			return (1);
		else if (str[0] >= 192 && str[0] <= 223)
			return (2);
		else if (str[0] >= 224 && str[0] <= 239)
			return (3);
		else if (str[0] >= 240 && str[0] <= 247)
			return (4);
		else if (str[0] >= 248 && str[0] <= 251)
			return (5);
		else if (str[0] >= 252 && str[0] <= 253)
			return (6);
	}
	return (0);
}
