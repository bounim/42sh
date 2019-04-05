/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 15:30:30 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/05 15:19:53 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int		built_debug(char **arg, t_envl *envl)
{
	(void)envl;
	if (!arg[1])
	{
		ft_putstr_fd("debug: usage: debug [name ...]\n", 2);
		return (1);
	}
	if (ft_strequ(arg[1], "ON"))
		g_shell.debug_mode = 1;
	else if (ft_strequ(arg[1], "OFF"))
		g_shell.debug_mode = 0;
	return (0);
}
