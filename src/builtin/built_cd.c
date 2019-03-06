/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:24:31 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/06 19:29:20 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"
/*
static char			*get_cd_path(t_env *env, char *arg)
{
	char	*tmp;

	tmp = NULL;
	if (arg == NULL)
	{
		if ((tmp = ft_search_env("HOME", env)))
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
*/
static t_envl		*init_pwd(t_env *env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	env = ft_setenv_c("PWD", cwd, env);
	push_env,
	return (env);
}

static t_envl		*ft_cd_oldpwd(t_envl *env)
{
	char	*tmp;
	char	*pwd;
	char	*cwd;

	tmp = NULL;
	pwd = NULL;
	cwd = NULL;
	if (!(tmp = ft_search_env("OLDPWD", env)))
	{
		ft_putendl_fd("cd : OLDPWD not set", 2);
		return (env);
	}
	cwd = ft_strdup(tmp);
	if (!(pwd = get_env_val(env, "PWD")))
		pwd = "";
	push_env(&env, "OLDPWD", pwd);
	chdir(cwd);
	ft_strdel(&cwd);
	cwd = getcwd(NULL, 0);
	push_env(&env, "PWD", cwd);
	return (env);
}

t_env				*built_cd(char **arg, t_envl *env)
{
	char	*path;
	char	*cwd;
	char	*pwd;
	size_t	i;

	i = first_arg(arg);
	if (ft_strequ(list->arg[1], "-"))
		return (env = ft_cd_oldpwd(env));
	env = init_pwd(env);
	path = get_cd_path(env, list->arg[1]);
	if (check_error_path(path, list->arg[1]) == -1)
		return (env);
	if (path)
	{
		pwd = ft_search_env("PWD", env);
		env = ft_setenv_c("OLDPWD", ft_strdup(pwd), env);
		chdir(path);
		cwd = getcwd(NULL, 0);
		env = ft_setenv_c("PWD", cwd, env);
	}
	return (env);
}
