/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 09:59:06 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/30 15:05:15 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static char			*get_cd_path(t_envl *env, char *arg)
{
	char	*tmp;

	tmp = NULL;
	if (arg == NULL)
	{
		if ((tmp = get_env_val(envl, "HOME")))
			return (tmp);
		else
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return (NULL);
		}
	}
	else
		return (arg);
}

static int			check_error_path(char *path, char *arg)
{
	struct stat		stbuf;
	DIR				*diropen;

	if (path == NULL)
		return (-1);
	if (lstat(path, &stbuf) == -1)
	{
		ft_no_such_file_or_dir("cd: ", arg);
		return (-1);
	}
	if (!S_ISDIR(stbuf.st_mode) && !S_ISLNK(stbuf.st_mode))
	{
		ft_not_dir("cd: ", arg);
		return (-1);
	}
	if (!(diropen = opendir(path)))
	{
		ft_permission_denied("cd: ", arg);
		return (-1);
	}
	else
		closedir(diropen);
	return (1);
}

static void		init_pwd(t_envl **env)
{
	char	*cwd;

	if (!(cwd = g_shell.canonic_path))
		cwd = getcwd(NULL, 0);
	push_env(env, "PWD", cwd);
}

static int		*ft_cd_oldpwd(t_envl *env)
{
	char	*tmp;
	char	*pwd;
	char	*cwd;

	tmp = NULL;
	pwd = NULL;
	cwd = NULL;
	if (!(tmp = get_env_val(env, "OLDPWD")))
	{
		ft_putendl_fd("cd : OLDPWD not set", 2);
		return (1);
	}
	cwd = ft_strdup(tmp);
	if (!(pwd = get_env_val(env, "PWD")))
		pwd = "";
	push_env(&g_shell.envl, "OLDPWD", pwd);
	chdir(cwd);
	ft_strdel(&cwd);
	cwd = getcwd(NULL, 0);
	push_env(&g_shell.envl, "PWD", cwd);
	ft_strdel(&cwd);
	return (0);
}

int				built_cd(char **arg, t_env *envl)
{
	char	*path;
	char	*cwd;
	char	*pwd;

	if (ft_arrlen(arg) > 2)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (1);
	}
	if (ft_strequ(arg[1], "-"))
		return (ft_cd_oldpwd(envl));
	init_pwd(&envl);
	path = get_cd_path(envl, arg[1]);
	if (check_error_path(path, arg[1]) == -1)
		return (1);
	if (path)
	{
		pwd = get_env_val(envl, "PWD");
		env = push_env(&g_shell.envl, "OLDPWD", pwd);
		chdir(path);
		cwd = getcwd(NULL, 0);
		env = push_env(&g_shell.envl, "PWD", cwd);
	}
	return (0);
}
