/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 19:25:02 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/02 17:06:54 by khsadira         ###   ########.fr       */
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

static char	**canonic_path_rework_tab(char **cwd_t, int *k)
{
	char	**ret;
	int		i;
	int		j;

	j = 0;
	i = ft_arrlen(cwd_t);
	if (!(ret = (char **)malloc(sizeof(char *) * i + 1)))
		return (NULL);
	ret[i + 1] = NULL;
	i = 0;
	j = 0;
	while (cwd_t[i])
	{
		if (ft_strequ(cwd_t[i], ".."))
		{
			if (j > 0)
				j--;
		}
		else if (!ft_strequ(cwd_t[i], "."))
			ret[j++] = ft_strdup(cwd_t[i]);
		i++;
	}
	*k = j;
	return (ret);
}

static char	*rework_canonic_path(char *cwd)
{
	char	**cwd_t;
	char	**ret_t;
	int		i;
	int		j;

	if (!(cwd_t = ft_strsplit(cwd, '/')))
	{
		ft_strdel(&cwd);
		return (NULL);
	}
	i = 0;
	if (!(ret_t = canonic_path_rework_tab(cwd_t, &j)))
		return (NULL);
	ft_strdel(&cwd);
	cwd = ft_strdup("");
	if (j == 0)
		cwd = ft_strdup("/");
	while (i < j)
	{
		cwd = ft_strjoin(cwd, "/");
		cwd = ft_strfjoin(cwd, ret_t[i++], 0);
	}
	ft_arrdel(cwd_t);
	ft_arrdel(ret_t);
	return (cwd);
}

static char	*search_path(char *arg, t_envl *envl, char *cwd)
{
	if (!arg)
	{
		if (!(cwd = ft_strdup(get_env_val(envl, "HOME"))))
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return (NULL);
		}
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
	if (opts)
		path = ft_strdup(*(arg + i));
	else if (!(path = search_path(*(arg + i), envl, NULL)))
		return (1);
	if (!(oldpwd = ft_strdup(get_env_val(envl, "PWD"))))
	{
		ft_strdel(&path);
		return (1);
	}
	if (chdir(path))
		return (cd_path_failed_perror(*(arg + i), path, oldpwd));
	if (opts)
	{
		ft_strdel(&path);
		path = getcwd(NULL, 0);
	}
	printf("path = %s\noldpwd = %s\n", path, oldpwd);
	return (cd_push_env)(path, oldpwd);
}
