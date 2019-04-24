/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:40:47 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/24 18:40:49 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static char	*cd_oldpwd(t_envl *envl)
{
	char	*tmp;

	if (!(tmp = ft_strdup(get_env_val(envl, "OLDPWD"))) || ft_strlen(tmp) == 0)
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		return (NULL);
	}
	return (tmp);
}

static char	*search_path(char *arg, t_envl *envl, char *cwd, int opts)
{
	if (opts)
		return (ft_strdup(arg));
	if (!arg)
	{
		if (!(cwd = ft_strdup(get_env_val(envl, "HOME"))))
			ft_putendl_fd("cd: HOME not set", 2);
		return (cwd);
	}
	if (!ft_strnequ(arg, "/", 1))
	{
		if (ft_strequ(arg, "-"))
			return (cd_oldpwd(envl));
		if (g_shell.canonic_path)
			cwd = ft_strdup(g_shell.canonic_path);
		else if (!(cwd = ft_strdup(get_env_val(envl, "PWD"))))
			if (!(cwd = getcwd(NULL, 0)))
				return (NULL);
		cwd = ft_strfjoin(cwd, "/", 0);
		cwd = ft_strfjoin(cwd, arg, 0);
	}
	else
		cwd = ft_strdup(arg);
	cwd = rework_canonic_path(cwd);
	return (cwd);
}

static int	cd_path_failed_perror(char *arg, char *path, char *oldpwd)
{
	ft_putstr_fd("sh: cd: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	ft_strdel(&path);
	ft_strdel(&oldpwd);
	return (1);
}

static int	cd_push_env(char *path, char *oldpwd)
{
	ft_strdel(&g_shell.canonic_path);
	g_shell.canonic_path = ft_strdup(path);
	push_env(&g_shell.envl, "OLDPWD", oldpwd, 1);
	push_env(&g_shell.envl, "PWD", path, 1);
	ft_strdel(&path);
	ft_strdel(&oldpwd);
	return (0);
}

int			built_cd(char **arg, t_envl *envl)
{
	char	*path;
	char	*oldpwd;
	size_t	i;
	int		opts;

	opts = 0;
	if (!(i = cd_first_arg(arg, &opts)))
		return (1);
	else if (!(path = search_path(*(arg + i), envl, NULL, opts)))
		return (1);
	if (!(oldpwd = ft_strdup(get_env_val(envl, "PWD"))))
	{
		ft_strdel(&path);
		return (1);
	}
	if (chdir(path))
		return (cd_path_failed_perror(*(arg + i), path, oldpwd));
	if (ft_strequ(arg[i], "-"))
		ft_putendl(path);
	if (opts)
	{
		ft_strdel(&path);
		path = getcwd(NULL, 0);
	}
	return (cd_push_env(path, oldpwd));
}
