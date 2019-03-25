/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 16:12:00 by kberisha          #+#    #+#             */
/*   Updated: 2019/03/03 16:14:55 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memtoi(const uint8_t *str, size_t size)
{
	size_t	i;
	int		neg;
	int		nbr;

	i = 0;
	neg = 0;
	nbr = 0;
	while (i < size && ft_isspace(str[i]))
		i++;
	if (i == size)
		return (0);
	if (str[i] == '-')
		neg = 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (i < size && ft_isdigit(str[i]))
	{
		nbr *= 10;
		nbr += ((int)str[i] - '0');
		i++;
	}
	if (neg)
		return (-nbr);
	else
		return (nbr);
}
