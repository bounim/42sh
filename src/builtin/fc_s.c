/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:31:18 by aguillot          #+#    #+#             */
/*   Updated: 2019/05/02 15:03:49 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int			fc_s(uint8_t **buff, int len)
{
	if (len <= 0)
		return (1);
	if (*buff[len - 1] != '\n')
		*(buff) = (uint8_t*)ft_strfjoin((char*)*buff, "\n", 0);
	ft_putstr((char*)buff);
	return (0);
}
