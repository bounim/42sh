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

static int		execute_utility(char **arg, t_envl *envl)
{
	char	path[PATH_MAX + 1];
	int		r;
	t_job	*new_job;

	new_job = NULL;
	if (!arg[0])
		return (125);
	if ((r = find_command(path, arg[0], envl)) != 0)
	{
		r = env_exit(arg[0], r);
		ft_arrdel(arg);
		free_envl(envl);
		return (r);
	}
	create_proc_argv(&new_job, path, arg, envl);
	ft_arrdel(arg);
	free_envl(envl);
	launch_job(&new_job);
	return (g_shell.exit_code);
}

static int		exec_env(char **start, t_envl *head)
{
	char	**arg;

	if (start == NULL)
	{
		print_envl(head, 0);
		free_envl(head);
		return (0);
	}
	arg = from_arg_to_cmd(start);
	return (execute_utility(arg, head));
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
