/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_input_controler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:16:41 by schakor           #+#    #+#             */
/*   Updated: 2019/04/04 14:55:51 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void		build_key(uint8_t *key, size_t *keylen, const uint8_t *input)
{
	*(key + *keylen) = *input;
	(*keylen)++;
}

void		build_count(uint8_t *key, size_t *keylen, int mode)
{
	size_t		i;
	ssize_t		rd;

	g_shell.edit.count = 1;
	if (*keylen == 1 && key[0] >= '1' && key[0] <= '9'
			&& mode == MODE_VI_COMMAND)
	{
		g_shell.edit.count = key[0] - '0';
		i = 0;
		while (i < 6)
		{
			if ((rd = read(0, key, 6)) < 0)
				fatal_exit(SH_EINVAL);
			i++;
			*keylen = (size_t)rd;
			if (i == 6)
				break ;
			if (!(rd == 1 && (key[0] >= '0' && key[0] <= '9')))
				break ;
			else if (key[0] >= '0' && key[0] <= '9')
				g_shell.edit.count = g_shell.edit.count * 10 + key[0] - '0';
		}
	}
}
