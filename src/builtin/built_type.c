/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 10:46:11 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/29 16:25:51 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int			name_is_alias(char *name)
{
	t_alias			*tmp;

	tmp = g_shell.alias;
	if (tmp)
	{
		while (tmp)
		{
			if (ft_strequ(tmp->name, name))
			{
				ft_putstr_fd(name, STDOUT_FILENO);
				ft_putstr_fd(" is aliased to `", STDOUT_FILENO);
				ft_putstr_fd(tmp->value, STDOUT_FILENO);
				ft_putstr_fd("'\n", STDOUT_FILENO);
				return (TRUE);
			}
			tmp = tmp->next;
		}
	}
	return (FALSE);
}

static int			name_is_builtin(char *name)
{
	static void		*builtin[12] = {"cd", "echo", "env", "setenv",
							"unsetenv", "set", "unset", "export",
							"alias", "unalias", "type", NULL};
	size_t			i;

	i = 0;
	while (builtin[i])
	{
		if (ft_strequ(builtin[i], name))
		{
			ft_putstr_fd(name, STDOUT_FILENO);
			ft_putstr_fd(" is a shell builtin\n", STDOUT_FILENO);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

static int			name_is_file(char *name, t_envl *envl, int is_file)
{
	char			**paths;
	char			*fullpath;
	char			*tmp;
	size_t			i;

	if (!(paths = ft_strsplit(get_env_val(envl, "PATH"), ':')))
		return (FALSE);
	tmp = ft_strjoin("/", name);
	i = 0;
	while (paths[i])
	{
		fullpath = ft_strjoin(paths[i], tmp);
		if (access(fullpath, F_OK) == 0)
		{
			ft_putstr_fd(name, STDOUT_FILENO);
			ft_putstr_fd(" is ", STDOUT_FILENO);
			ft_putendl_fd(fullpath, STDOUT_FILENO);
			is_file = TRUE;
			break ;
		}
		i++;
	}
	ft_arrdel(paths);
	ft_strdel(&tmp);
	return (is_file);
}

static void			print_type(char *name, int *all_found, t_envl *envl)
{
	if (name_is_alias(name))
		return ;
	else if (name_is_builtin(name))
		return ;
	else if (name_is_file(name, envl, FALSE))
		return ;
	else
	{
		ft_putstr_fd("sh: type: ", STDERR_FILENO);
		ft_putstr_fd(name, STDERR_FILENO);
		ft_putstr_fd(": not found\n", STDERR_FILENO);
		*all_found = FALSE;
	}
}

int					built_type(char **arg, t_envl *envl)
{
	size_t			i;
	int				all_found;

	if (!arg)
		return (1);
	all_found = TRUE;
	i = 1;
	while (arg[i])
	{
		print_type(arg[i], &all_found, envl);
		i++;
	}
	return (all_found);
}
