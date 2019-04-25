/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 15:18:44 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/15 14:54:58 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int		built_exit(char **arg, t_envl *envl)
{
	(void)envl;
	file_from_history(g_shell.hist.history);
	clean_shell();
	ft_putstr("exit\n");
	if (arg)
		if (arg[1])
			exit(ft_atoi(arg[1]));
	exit(0);
}
