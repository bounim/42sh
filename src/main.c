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

t_shell				g_shell;

int		main(int ac, char **av, char **env)
{
	//init_signals();
	init_shell(ac, av, env);
	run_shell();
	clean_shell();
	exit(EXIT_SUCCESS);
}
