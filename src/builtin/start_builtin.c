/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 15:23:17 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/24 13:19:37 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static t_builtin	g_builtin[] = {
	{"alias", built_alias},
	{"cd", built_cd},
	{"debug", built_debug},
	{"echo", built_echo},
	{"env", built_env},
	{"exit", built_exit},
	{"export", built_export},
	{"hash", built_hash},
	{"history", built_history},
	{"set", built_set},
	{"setenv", built_setenv},
	{"test", built_test},
	{"type", built_type},
	{"unalias", built_unalias},
	{"unset", built_unset},
	{"unsetenv", built_unsetenv},
};

int					check_builtin(char *cmd)
{
	size_t	i;

	i = 0;
	while (i < sizeof(g_builtin) / sizeof(g_builtin[0]))
	{
		if (ft_strequ(cmd, g_builtin[i].name))
			return (1);
		i++;
	}
	return (0);
}

int					start_builtin(char **arg, t_envl *envl)
{
	size_t	i;

	if (!arg || !arg[0])
		return (-1);
	i = 0;
	while (i < sizeof(g_builtin) / sizeof(g_builtin[0]))
	{
		if (ft_strequ(arg[0], g_builtin[i].name))
			return (g_builtin[i].func(arg, envl));
		i++;
	}
	return (-1);
}
