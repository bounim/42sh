/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 15:18:44 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/22 15:36:23 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int		built_exit(char **arg)
{
	file_from_history(get_env_val(g_shell.envl, "HOME"), g_shell.hist.history);

	//free_all
	if (arg[1])
		return (ft_atoi(arg[1]));
	return (0);
}
