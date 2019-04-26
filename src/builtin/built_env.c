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

static int		execute_utility(char **arg, char **env)
{
	pid_t	pid;
	int		status;
	t_envl	*envl;
	char	*path;

	envl = NULL;
	set_signal_dfl();
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid > 0)
	{
		waitpid(pid, &status, WUNTRACED | WCONTINUED);
		g_shell.exit_code = get_return_status(status);
		return (g_shell.exit_code);
	}
	if (!arg[0])
		return (125);
	else if ((env && !(envl = envarr_to_envl(env)))
	|| !(path = find_command(arg[0], envl)))
		return (env_exit(arg[0]));
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

static void		init_cor(char **arg, t_envl *envl, t_cor *cor)
{
	cor->arg_ptr = arg + 1;
	cor->dup_env = dup_envl(envl);
	cor->name = NULL;
	cor->start = NULL;
	cor->opt = 1;
}

int				built_env(char **arg, t_envl *envl)
{
	t_cor	cor;
	char	*ptr;

	init_cor(arg, envl, &cor);
	while (*(cor.arg_ptr))
	{
		if (!ft_strcmp(*(cor.arg_ptr), "-i") && cor.opt)
		{
			free_envl(cor.dup_env);
			cor.dup_env = NULL;
		}
		else if (cor.opt && !ft_strcmp(*(cor.arg_ptr), "--"))
			cor.opt = 0;
		else if ((ptr = ft_strchr(*(cor.arg_ptr), '=')) && is_valid_name(*arg))
		{
			cor.name = ft_strsub(*cor.arg_ptr, 0, ptr - *(cor.arg_ptr));
			push_env(&(cor.dup_env), cor.name, ptr + 1, 1);
			cor.opt = 0;
		}
		else if ((!cor.opt || (*(cor.arg_ptr))[0] != '-') && cor.start == NULL)
			cor.start = cor.arg_ptr;
		(cor.arg_ptr)++;
	}
	exec_env(cor.start, cor.dup_env);
	return (0);
}
