/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u8_strsplit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <schakor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 13:18:50 by schakor           #+#    #+#             */
/*   Updated: 2019/02/16 13:20:22 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uint8_t		**ft_u8_strsplit(uint8_t const *s, uint8_t c)
{
	return ((uint8_t **)ft_strsplit((char const *)s, (char)c));
}
