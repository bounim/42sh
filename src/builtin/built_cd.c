/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:24:31 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/22 16:31:07 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

char	*rework_canonic_path(char *canonic_path)
{
	int		nb_bfr;
	int		i;
	int		j;
	char	*tmp;
	char	**canonic_tab;

	j = 0;
	if (!canonic_path)
		return (canonic_path);
	tmp = canonic_path;
	if (tmp && tmp[0] == '/')
		j = 1;
	canonic_tab = ft_strsplit(tmp, '/');
	i = 0;
	nb_bfr = 0;
	while (canonic_tab[i])
	{
		if (ft_strequ(canonic_tab[i], ".."))
			nb_bfr++;
		i++;
	}
	if (nb_bfr == 0)
		return (canonic_path);
	i -= nb_bfr;
	if (j)
		tmp = ft_strdup("/");
	j = 0;
	while (j < i && nb_bfr--)
	{
		tmp = ft_strfjoin(tmp, canonic_tab[j], 0);
		j++;
		i++;
		if (j < i)
			tmp = ft_strfjoin(tmp, "/", 0);
		free(canonic_tab[j]);
	}
	free(canonic_tab);
	g_shell.canonic_path = tmp;
	return (tmp);
}

static char			*get_opts_path(char *arg)
{
	struct stat	buf;
	char		link[255];
	int			rl;
	char		*tmp;

	rl = 0;
	if (lstat(arg, &buf) == -1)
		return (NULL);
	else if (!S_ISLNK(buf.st_mode))
		return (arg);
	else if ((rl = readlink(arg, link, 255)) == -1)
		return (NULL);
	link[rl] = '\0';
	tmp = ft_strdup("/");
	tmp = ft_strfjoin(tmp, link, 0);
	return (tmp);
}

static char			*get_cd_path(t_envl *env, char *arg, int opts)
{
	char	*tmp;

	tmp = NULL;
	if (arg == NULL)
	{
		if ((tmp = get_env_val(env, "HOME")))
			return (tmp);
		else
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return (NULL);
		}
	}
	else if (ft_strequ(arg, "..") && g_shell.canonic_path) //strnequ ??
	{
		tmp = ft_strdup(g_shell.canonic_path);
		tmp = ft_strfjoin(tmp, "/..", 0);
		tmp = rework_canonic_path(tmp);
		return (tmp);
	}
	else if (opts == 1)
	{
		tmp = get_opts_path(arg);
		return (tmp);
	}
	return (arg);
}

static int		init_pwd(t_envl **env)
{
	char	*cwd;
	char	*tmp;
	int		stock;

	stock = 0;
	tmp = get_env_val(*env, "PWD");
	if (tmp)
		return (0);
	if (g_shell.canonic_path)
	{
		stock = 1;
		cwd = ft_strdup(g_shell.canonic_path);
	}
	else if (!(cwd = getcwd(NULL, 0)))
	{
		write(2, "cd: GETCWD error\n", 17);
		return (1);
	}
	if (stock)
		g_shell.canonic_path = cwd;
	push_env(env, "PWD", cwd, 1);
	return (0);
}

static int		cd_oldpwd(t_envl *env)
{
	char	*pwd;
	char	*oldpwd;
	char	*tmp;

	tmp = NULL;
	pwd = NULL;
	oldpwd = NULL;
	if (!(tmp = get_env_val(env, "OLDPWD")))
	{
		write(2, "cd: OLDPWD not set\n", 19);
		return (1);
	}
	oldpwd = ft_strdup(tmp);
	if (g_shell.canonic_path)
		pwd = ft_strdup(g_shell.canonic_path);
	else
	{
		if (!(tmp = ft_strdup(get_env_val(env, "PWD"))))
		{
			if (!(tmp = getcwd(NULL, 0)))
			{
				write(2, "cd: dir not found\n", 17);
				return (1);
			}
		}
		pwd = ft_strdup(tmp);
	}
	if (chdir(oldpwd) == -1)
	{
		ft_putendl_fd("cd: CHDIR error", 2);
		return (1);
	}
	g_shell.canonic_path = ft_strdup(oldpwd);
	push_env(&g_shell.envl, "OLDPWD", pwd, 1);
	push_env(&g_shell.envl, "PWD", oldpwd, 1);
	return (0);
}

static int		cd_first_arg(char **arg, int *opts)
{
	int	i;
	int	l;
	int	j;

	l = 0;
	i = 1;
	while (arg[i] != NULL)
	{
		if (ft_strequ(arg[i], "-"))
				return (i);
		if (ft_strequ(arg[i], "--"))
			return (i + 1);
		else if (ft_strnequ(arg[i], "-", 1))
		{
			j = 1;
			while (arg[i][j])
			{
				if (arg[i][j] == 'P' && *opts != -1)
					*opts = 1;
				else if (arg[i][j] != 'L' && arg[i][j] != 'P')
				{
					ft_putstr_fd("sh: cd: -", 2);
					write(2, arg[i] + j, 1);
					ft_putstr_fd(": invalid option\ncd: usage: cd [-L|-P] [dir]\n", 2);
					return (-1);
				}
				else
					*opts = -1;
				j++;
			}
		}
		else
			return (i);
		i++;
	}
	return (i);
}

int				built_cd(char **arg, t_envl *envl)
{
	char	*path;
	char	*oldpwd;
	size_t	i;
	int		opts;

	opts = 0;
	if ((i = cd_first_arg(arg, &opts)) == -1)
		return (1);
	if (opts == -1)
		opts = 0;
	if (init_pwd(&envl))
		return (1);
	if (ft_strequ(arg[i], "-"))
	{
		cd_oldpwd(envl);
		return (1);
	}
	if ((oldpwd = get_env_val(envl, "PWD")))
		oldpwd = ft_strdup(oldpwd);
	else
		oldpwd = ft_strdup("");
	if (!(path = get_cd_path(envl, arg[i], opts)))
		return (1);
	g_shell.canonic_path = ft_strdup(path);
	if (chdir(path) == -1)
	{
		ft_putendl_fd("cd: dir not found", 2);
		return (1);
	}
	push_env(&g_shell.envl, "OLDPWD", oldpwd, 1);
	push_env(&g_shell.envl, "PWD", path, 1);
	return (0);
}
