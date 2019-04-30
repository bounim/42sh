/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:27:12 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/15 14:51:01 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int		parent_proc(pid_t pid)
{
	int status;

	waitpid(pid, &status, WUNTRACED);
	if (WIFSTOPPED(status))
	{
		kill(pid, SIGTERM);
		kill(pid, SIGCONT);
	}
	g_shell.exit_code = get_return_status(status);
	tcsetpgrp(0, g_shell.pgid);
	return (g_shell.exit_code);
}

static int		execute_utility(char **arg, char **env)
{
	pid_t	pid;
	t_envl	*envl;
	char	path[PATH_MAX + 1];
	int		r;

	envl = NULL;
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid > 0)
		return (parent_proc(pid));
	clear_signals();
	r = -1;
	if (!arg[0])
		return (125);
	else if ((env && !(envl = envarr_to_envl(env)) && !ft_strchr(arg[0], '/'))
			|| (r = find_command(path, arg[0], envl)) != 0)
		return (env_exit(arg[0], r));
	execve(path, arg, env);
	fatal_exit(7);
	return (125);
}

static int		exec_env(char **start, t_envl *head)
{
	char	**ret;
	char	**env;
	int		r;

	r = 0;
	env = NULL;
	if (start == NULL)
	{
		print_envl(head, 0);
		free_envl(head);
	}
	else
	{
		ret = from_arg_to_cmd(start);
		env = envl_to_envarr(head);
		if (!env)
			return (125);
		r = execute_utility(ret, env);
		ft_free_arr(ret);
		ft_free_arr(env);
		free_envl(head);
	}
	return (r);
}

static void		env_assign(t_cor *c, char *ptr)
{
	c->name = ft_strsub(*c->t, 0, ptr - *(c->t));
	push_env(&(c->dup_env), c->name, ptr + 1, 1);
	ft_strdel(&(c->name));
	c->o = 0;
}

int				built_env(char **arg, t_envl *envl)
{
	t_cor	c;
	char	*ptr;

	init_cor(arg, envl, &c);
	while (*(c.t))
	{
		if (!ft_strcmp(*(c.t), "-i") && c.o)
		{
			free_envl(c.dup_env);
			c.dup_env = NULL;
		}
		else if (c.o && (!ft_strcmp(*(c.t), "--") || !ft_strcmp(*(c.t), "-")))
			c.o = 0;
		else if (c.o && ft_strcmp(*(c.t), "-i") && *(c.t[0]) == '-')
			return (env_usage(*(c.t), c.dup_env));
		else if ((ptr = ft_strchr(*(c.t), '=')) && is_valid_name(*arg))
			env_assign(&c, ptr);
		else if ((!c.o || (*(c.t))[0] != '-') && c.start == NULL)
		{
			c.o = 0;
			c.start = c.t;
		}
		(c.t)++;
	}
	return (exec_env(c.start, c.dup_env));
}
