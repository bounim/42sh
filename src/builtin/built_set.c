/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 11:29:37 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/13 18:35:29 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int		built_set(t_envl *envl)
{
	while (envl)
	{
		ft_putstr(envl->name);
		ft_putchar('=');
		ft_putstr(envl->value);
		ft_putchar(10);
		envl = envl->next;
	}
	return (0);
}
