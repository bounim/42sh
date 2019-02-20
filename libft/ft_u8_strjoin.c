/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u8_strjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <schakor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 11:51:22 by schakor           #+#    #+#             */
/*   Updated: 2019/02/16 12:31:47 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uint8_t			*ft_u8_strjoin(uint8_t const *s1, uint8_t const *s2)
{
	return ((uint8_t *)ft_strjoin((char const *)s1, (char const *)s2));
}
