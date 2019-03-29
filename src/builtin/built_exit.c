/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 15:18:44 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/29 17:40:49 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int		built_exit(char **arg)
{
	file_from_history(g_shell.hist.history);

	//free_all
	if (arg[1])
		exit(ft_atoi(arg[1]));
	exit(0);
}
