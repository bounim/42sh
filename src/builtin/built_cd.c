/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:24:31 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/06 22:31:19 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static char			*get_cd_path(t_envl *env, char *arg)
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
	else if (ft_strequ(arg, ".."))
	{
		tmp;
	}
	return (arg);
}

static int			check_error_path(char *path, char *arg)
{
	struct stat		stbuf;
	DIR				*diropen;
	/*
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

static int		init_pwd(t_env **env)
{
	char	*cwd;

	if (!(cwd = getcwd(NULL, 0)))
	{
		ft_putendl_fd("cd: GETCWD error");
		return (1);
	}
	push_env(&env, "PWD", cwd);
	return (0);
}

static int		cd_oldpwd(t_envl **env)
{
	char	*tmp;
	char	*pwd;
	char	*cwd;

	tmp = NULL;
	pwd = NULL;
	cwd = NULL;
	if (!(tmp = ft_search_env("OLDPWD", env)))
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		return (1);
	}
	cwd = ft_strdup(tmp);
	if (!(pwd = get_env_val(env, "PWD")))
		pwd = "";
	push_env(&env, "OLDPWD", pwd);
	if (chdir(cwd) == -1)
	{
		ft_putendl_fd("cd: CHDIR error", 2);
		return (1);
	}
	ft_strdel(&cwd);
	if (!(cwd = getcwd(NULL, 0)))
	{
		ft_putendl_fd("cd: GETCWD error", 2);
		return (1);
	}
	push_env(&env, "PWD", cwd);
	return (0);
}

static int		cd_first_arg(char **arg, int *opts)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_strequ(arg[i], "-P"))
			opts = 1;
		if (arg[i][0] && arg[i][0] == '-' &&
				arg[i][1] && (arg[i][1] != 'P' ||
					arg[i][1] != 'L' || arg[i][1] == '-'))
			return (i)
		else if (arg[i][0] && !arg[i][1])
			return (i);
		i++;
	}
	return (i);
}

int				built_cd(char **arg, t_envl **env)
{
	char	*path;
	char	*cwd;
	char	*pwd;
	size_t	i;
	int		opts;

	i = cd_first_arg(arg, &opts);
	if (ft_strequ(list->arg[i], "-"))
		return (cd_oldpwd(env));
	if (init_pwd(env))
		return (1);
	if (!(path = get_cd_path(env, arg[i], opts)))
		return (1);
	if (check_error_path(path, arg[i]) == -1)
		return (1);
	pwd = get_env_val(env, "PWD");
	push_env(&env, "OLDPWD", pwd);
	if (chdir(path) == -1)
	{
		ft_putendl_fd("cd: CHDIR error", 2);
		return (1);
	}
	if (!(cwd = getcwd(NULL, 0)))
	{
		ft_putendl_fd("cd: GETCWD error", 2);
		return (1);
	}
	push_env(&env, "PWD", cwd);
	return (0);
}
