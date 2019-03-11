/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 16:06:31 by emartine          #+#    #+#             */
/*   Updated: 2019/03/09 15:10:03 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"
//schakor repo commit 27a3f3151872d9f639afd3b305d4cf71bd37456b
//schakor repo commit 4ed25fab84387307a86d93d5b084a56919987b7d

t_shell				g_shell;

int		main(int ac, char **av, char **env)
{
	//init_signals();
	init_shell(ac, av, env);
	run_shell();
	clean_shell();
	exit(EXIT_SUCCESS);
}
