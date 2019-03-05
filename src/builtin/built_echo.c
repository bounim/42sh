/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:28:32 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/04 12:07:32 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int	built_echo(uint8_t **arg, int *arg_size)
{
	int		n;
	int		i;

	i = 0;
	n = 0;
	if (arg[0] && !ft_memcmp(arg[0], "-n\0", 3))
	{
		n = 1;
		i++;
	}
	while (arg[i])
	{
		if (arg[i + 1])
			write(1, " ", 1);
		write(1, arg[i], arg_size[i]);
	}
	if (!n)
		write(1, "\n", 1);
	return (0);
}
