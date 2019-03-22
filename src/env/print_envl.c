/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_envl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 16:42:59 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/22 18:17:18 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	print_envl(t_envl *env, int exp)
{
	while (env)
	{
		if (env->exp == 1)
		{
			if (exp == 1)
				ft_putstr("export ");
			ft_putstr(env->name);
			ft_putchar('=');
			if (env->value)
				ft_putstr(env->value);
			ft_putchar('\n');
		}
		env = env->next;
	}
}
