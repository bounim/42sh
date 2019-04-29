/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:40:47 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/25 15:14:46 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static char	*cd_oldpwd(t_envl *envl)
{
	char	*tmp;

	tmp = NULL;
	if (!(tmp = ft_strdup(get_env_val(envl, "OLDPWD"))) || ft_strlen(tmp) == 0)
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		ft_strdel(&tmp);
		return (NULL);
	}
	return (tmp);
}

static char	*search_path(char *arg, t_envl *envl, char *cwd, int opts)
{
	if (ft_strequ(arg, "-"))
		return (cd_oldpwd(envl));
	if (!arg)
	{
		if (!(cwd = ft_strdup(get_env_val(envl, "HOME"))))
			ft_putendl_fd("cd: HOME not set", 2);
		return (cwd);
	}
	if (!ft_strnequ(arg, "/", 1))
	{
		if (opts)
			return (find_cdpath(arg, envl, opts));
		if (!(cwd = find_cdpath(arg, envl, opts)))
			return (NULL);
	}
	else
		cwd = ft_strdup(arg);
	cwd = rework_canonic_path(cwd);
	return (cwd);
}

static int	cd_path_failed_perror(char *arg, char *path, char *oldpwd)
{
	int			ret;
	struct stat	sb;

	ret = 0;
	if (access(path, F_OK) || path == NULL)
		ret = 1 + put_error(NULL, "cd", arg, "No such file or directory\n");
	else if (access(path, X_OK))
		ret = 1 + put_error(NULL, "cd", arg, "Permission denied\n");
	else if (lstat(path, &sb) == 0 && (!S_ISDIR(sb.st_mode)
				&& !S_ISLNK(sb.st_mode)))
		ret = 1 + put_error(NULL, "cd", arg, "Not a directory\n");
	else if (chdir(path))
		ret = 1 + put_error(NULL, "cd", arg, "Unable to process\n");
	if (ret == 1)
	{
		ft_strdel(&path);
		ft_strdel(&oldpwd);
		return (1);
	}
	return (0);
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

	oldpwd = NULL;
	if (!(i = cd_first_arg(arg, &opts)))
		return (1);
	if (!(path = search_path(*(arg + i), envl, NULL, opts)))
		return (1);
	if ((oldpwd = ft_strdup(get_env_val(envl, "PWD"))) == NULL)
	{
		ft_strdel(&path);
		return (1);
	}
	if (cd_path_failed_perror(*(arg + i), path, oldpwd))
		return (1);
	if (ft_strequ(arg[i], "-"))
		ft_putendl(path);
	if (opts)
	{
		ft_strdel(&path);
		path = getcwd(NULL, 0);
	}
	return (cd_push_env(path, oldpwd));
}
