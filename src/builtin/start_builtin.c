/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 15:52:24 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/26 15:22:59 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	start_builtin_env(char **arg, t_envl *env)
{
	if (ft_strequ(arg[0], "alias"))
		built_alias(arg, &g_shell.alias);
	else if (ft_strequ(arg[0], "unalias"))
		built_unalias(arg, &g_shell.alias);
	else if (ft_strequ(arg[0], "export"))
		built_export(arg, env);
	else if (ft_strequ(arg[0], "cd"))
		built_cd(arg, env);
	else if (ft_strequ(arg[0], "debug"))
		built_debug(arg);
	else if (ft_strequ(arg[0], "echo"))
		built_echo(arg);
	else if (ft_strequ(arg[0], "env"))
		built_env(arg, env);
	else if (ft_strequ(arg[0], "history"))
		built_history(arg, &g_shell.hist.history);
	else if (ft_strequ(arg[0], "set"))
		built_set(env);
	else if (ft_strequ(arg[0], "setenv"))
		built_setenv(arg, env);
	else if (ft_strequ(arg[0], "unset"))
		built_unset(arg, env);
	else if (ft_strequ(arg[0], "unsetenv"))
		built_unsetenv(arg, env);
	else if (ft_strequ(arg[0], "type"))
		built_type(arg, env);
	else if (ft_strequ(arg[0], "exit"))
		exit(built_exit(arg));
	else
		return (0);
	return (1);
}

static int	start_builtin_null(char **arg)
{
	if (ft_strequ(arg[0], "alias"))
		built_alias(arg, &g_shell.alias);
	else if (ft_strequ(arg[0], "unalias"))
		built_unalias(arg, &g_shell.alias);
	else if (ft_strequ(arg[0], "export"))
		built_export(arg, NULL);
	else if (ft_strequ(arg[0], "cd"))
		built_cd(arg, g_shell.envl);
	else if (ft_strequ(arg[0], "debug"))
		built_debug(arg);
	else if (ft_strequ(arg[0], "echo"))
		built_echo(arg);
	else if (ft_strequ(arg[0], "env"))
		built_env(arg, g_shell.envl);
	else if (ft_strequ(arg[0], "history"))
		built_history(arg, &g_shell.hist.history);
	else if (ft_strequ(arg[0], "set"))
		built_set(g_shell.envl);
	else if (ft_strequ(arg[0], "setenv"))
		built_setenv(arg, NULL);
	else if (ft_strequ(arg[0], "unset"))
		built_unset(arg, NULL);
	else if (ft_strequ(arg[0], "unsetenv"))
		built_unsetenv(arg, NULL);
	else if (ft_strequ(arg[0], "type"))
		built_type(arg, g_shell.envl);
	else if (ft_strequ(arg[0], "exit"))
		exit(built_exit(arg));
	else
		return (0);
	return (1);
}

int		start_builtin(char **arg, t_envl *envl)
{
	int		i;

	i = 1;
	if (!arg[0])
			return (0);
	if (envl)
	{
		i = start_builtin_env(arg, envl);
		free_envl(envl);
	}
	else if (g_shell.envl)
		i = start_builtin_null(arg);
	return (i);
}
