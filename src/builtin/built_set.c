/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 11:29:37 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/05 14:34:45 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int		built_set(char **arg, t_envl *envl)
{
	(void)arg;
	while (envl)
	{
		if (envl->read_only < 2)
		{
			ft_putstr(envl->name);
			ft_putchar('=');
			ft_putstr(envl->value);
			ft_putchar(10);
		}
		envl = envl->next;
	}
	return (0);
}
