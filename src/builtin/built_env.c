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

static int		env_exit(char *str)
{
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": no such file or directory", 2);
	exit(EXIT_FAILURE);
	return (-1);
}

static char		**from_arg_to_cmd(char **arg, int start)
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

static int		execute_utility(char **arg, char **env)
{
	pid_t	pid;
	int		status;
	t_envl	*envl;
	char	*path;

	envl = NULL;
	if (!arg)
		return (-1); //TODO error
	set_signal_dfl();
	pid = fork();
	if (pid < 0)
		return (-1); //TODO error
	else if (pid > 0)
	{
		ft_putendl("in parent process");
		waitpid(pid, &status, WUNTRACED | WCONTINUED);
		g_shell.exit_code = get_return_status(status);
		return (0);
	}
	ft_putendl("in child process");
	if (arg[0] && ft_strchr(arg[0], '/'))
		path = ft_strdup(arg[0]);
	else if (arg[0])
	{
		if ((env && !(envl = envarr_to_envl(env)))
			|| !(path = find_command(arg[0], envl)))
			return (env_exit(arg[0])); //TODO error
	}
	else if (!arg[0])
		return (-1); //TODO error
	execve(path, arg, env);
	fatal_exit(7);
	return (-1);
}

static int		exec_env(char **arg, int start, size_t i, t_envl *head)
{
	char	**ret;
	char	**env;
	int 	r;

	r = 0;
	env = NULL;
	printf("start = %d && i = %zu\n", start, i);
	if (start == -1)
	{
		ft_putendl("built env");
		print_envl(head, 0);
		free_envl(head);
	}
	else
	{
		ret = from_arg_to_cmd(arg, start);
		env = envl_to_envarr(head);
		r = execute_utility(ret, env);
		ft_free_arr(ret);
		free_envl(head);
	}
	return (r);
}

int		is_valid_name(char *str)
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

int				built_env(char **arg, t_envl *envl)
{
	t_envl	*tmp;
	size_t	i, j;
	int		start;
	int		options;
	char	*name = NULL;

	i = 1;
	options = 1;
	start = -1;
	tmp = dup_envl(envl);
	while (arg[i])
	{
		if (!ft_strcmp(arg[i], "-i") && options)
		{
			free_envl(tmp);
			tmp = NULL;
		}
		else if (options && !ft_strcmp(arg[i], "--"))
			options = 0;
		else if (ft_strchr(arg[i], '=') && is_valid_name(arg[i]))
		{
			ft_putendl("pushing env");
			j = 0;
			while (arg[i][j] != '=')
				j++;
			if (!(name = malloc(j + 1)))
				return (-1);
			ft_memmove(name, arg[i], j);
			name[j] = '\0';
			/*if (!tmp)
			{
				if (!(tmp = malloc(sizeof(*tmp))))
					return (-1);
				ft_memset(tmp, 0, sizeof(*tmp));
			}*/
			push_env(&tmp, name, ft_strchr(arg[i], '=') + 1, 1);
			options = 0;
		}
		else if (!options || arg[i][0] != '-')
			start = i;
		i++;
	}
	exec_env(arg, start, i, tmp);
	return (0);
}
