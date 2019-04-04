/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 15:52:24 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/04 17:31:50 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	start_builtin_env(char **arg, t_envl *env)
{
	if (ft_strequ(arg[0], "alias"))
		push_env(&g_shell.envl, "?", ft_itoa(built_alias(arg, &g_shell.alias)), 0);
	else if (ft_strequ(arg[0], "unalias"))
		push_env(&g_shell.envl, "?", ft_itoa(built_unalias(arg, &g_shell.alias)), 0);
	else if (ft_strequ(arg[0], "export"))
		push_env(&g_shell.envl, "?", ft_itoa(built_export(arg, env)), 0);
	else if (ft_strequ(arg[0], "cd"))
		push_env(&g_shell.envl, "?", ft_itoa(built_cd(arg, env)), 0);
	else if (ft_strequ(arg[0], "debug"))
		push_env(&g_shell.envl, "?", ft_itoa(built_debug(arg)), 0);
	else if (ft_strequ(arg[0], "echo"))
		push_env(&g_shell.envl, "?", ft_itoa(built_echo(arg)), 0);
	else if (ft_strequ(arg[0], "env"))
		push_env(&g_shell.envl, "?", ft_itoa(built_env(arg, env)), 0);
	else if (ft_strequ(arg[0], "history"))
		push_env(&g_shell.envl, "?", ft_itoa(built_history(arg, &g_shell.hist.history)), 0);
	else if (ft_strequ(arg[0], "set"))
		push_env(&g_shell.envl, "?", ft_itoa(built_set(env)), 0);
	else if (ft_strequ(arg[0], "setenv"))
		push_env(&g_shell.envl, "?", ft_itoa(built_setenv(arg, env)), 0);
	else if (ft_strequ(arg[0], "unset"))
		push_env(&g_shell.envl, "?", ft_itoa(built_unset(arg, env)), 0);
	else if (ft_strequ(arg[0], "unsetenv"))
		push_env(&g_shell.envl, "?", ft_itoa(built_unsetenv(arg, env)), 0);
	else if (ft_strequ(arg[0], "type"))
		push_env(&g_shell.envl, "?", ft_itoa(built_type(arg, env)), 0);
	else if (ft_strequ(arg[0], "exit"))
		exit(built_exit(arg));
	else
		return (0);
	return (1);
}

static int	start_builtin_null(char **arg)
{
	if (ft_strequ(arg[0], "alias"))
		push_env(&g_shell.envl, "?", ft_itoa(built_alias(arg, &g_shell.alias)), 0);
	else if (ft_strequ(arg[0], "unalias"))
		push_env(&g_shell.envl, "?", ft_itoa(built_unalias(arg, &g_shell.alias)), 0);
	else if (ft_strequ(arg[0], "export"))
		push_env(&g_shell.envl, "?", ft_itoa(built_export(arg, NULL)), 0);
	else if (ft_strequ(arg[0], "cd"))
		push_env(&g_shell.envl, "?", ft_itoa(built_cd(arg, g_shell.envl)), 0);
	else if (ft_strequ(arg[0], "debug"))
		push_env(&g_shell.envl, "?", ft_itoa(built_debug(arg)), 0);
	else if (ft_strequ(arg[0], "echo"))
		push_env(&g_shell.envl, "?", ft_itoa(built_echo(arg)), 0);
	else if (ft_strequ(arg[0], "env"))
		push_env(&g_shell.envl, "?", ft_itoa(built_env(arg, g_shell.envl)), 0);
	else if (ft_strequ(arg[0], "history"))
		push_env(&g_shell.envl, "?", ft_itoa(built_history(arg, &g_shell.hist.history)), 0);
	else if (ft_strequ(arg[0], "set"))
		push_env(&g_shell.envl, "?", ft_itoa(built_set(g_shell.envl)), 0);
	else if (ft_strequ(arg[0], "setenv"))
		push_env(&g_shell.envl, "?", ft_itoa(built_setenv(arg, NULL)), 0);
	else if (ft_strequ(arg[0], "unset"))
		push_env(&g_shell.envl, "?", ft_itoa(built_unset(arg, NULL)), 0);
	else if (ft_strequ(arg[0], "unsetenv"))
		push_env(&g_shell.envl, "?", ft_itoa(built_unsetenv(arg, NULL)), 0);
	else if (ft_strequ(arg[0], "type"))
		push_env(&g_shell.envl, "?", ft_itoa(built_type(arg, g_shell.envl)), 0);
	else if (ft_strequ(arg[0], "fg"))
		push_env(&g_shell.envl, "?", ft_itoa(built_fg(arg, g_shell.head_job)), 0);
	else if (ft_strequ(arg[0], "jobs"))
		push_env(&g_shell.envl, "?", ft_itoa(built_jobs(arg, g_shell.head_job)), 0);
	else if (ft_strequ(arg[0], "bg"))
		push_env(&g_shell.envl, "?", ft_itoa(built_bg(arg, g_shell.head_job)), 0);
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
