/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:52:10 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/26 14:57:41 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	env_exit(char *str)
{
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": No such file or directory", 2);
	exit(125);
	return (-1);
}

static char	**from_arg_to_cmd(char **arg, int start)
{
	int		nb_arg;
	char	**ret;
	int		i;
	int		g_size;

	i = 0;
	ret = NULL;
	nb_arg = start;
	while (arg[nb_arg])
		nb_arg++;
	g_size = nb_arg - start;
	if (!(ret = (char **)malloc(sizeof(char *) * (g_size + 1))))
		return (NULL);
	ret[g_size] = NULL;
	while (arg[start])
	{
		ret[i] = ft_strdup(arg[start]);
		i++;
		start++;
	}
	return (ret);
}

static int	execute_utility(char **arg, char **env)
{
	pid_t	pid;
	int		status;
	t_envl	*envl;
	char	*path;

	envl = NULL;
	set_signal_dfl();
	pid = fork();
	if (pid < 0)
		return (-1); //TODO error
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

int			exec_env(char **arg, int start, t_envl *head)
{
	char	**ret;
	char	**env;
	int		r;

	r = 0;
	env = NULL;
	if (start == -1)
	{
		print_envl(head, 0);
		free_envl(head);
	}
	else
	{
		ret = from_arg_to_cmd(arg, start);
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

int			is_valid_name(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] && ft_isdigit(str[i]))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
