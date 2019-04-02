/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 19:25:02 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/02 10:51:27 by khsadira         ###   ########.fr       */
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

static char	*get_lnk_path(char *arg)
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

static char	**canonic_path_rework_tab(char **cwd_t, int *k)
{
	char	**ret;
	int		i;
	int		j;

	j = 0;
	i = ft_arrlen(cwd_t);
	if (!(ret = (char **)malloc(sizeof(char *) * i + 1)))
		return (NULL);
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
		//ft_strdel(&cwd);
		return (NULL);
	}
	if (!(ret_t = canonic_path_rework_tab(cwd_t, &j)))
		return (NULL);
	//ft_strdel(&cwd);
	cwd = ft_strdup("");
	if (j == 0)
		cwd = ft_strdup("/");
	i = 0;
	while (i < j)
	{ //leaks
		cwd = ft_strjoin(cwd, "/");
		cwd = ft_strjoin(cwd, ret_t[i++]);
	}
//	ft_arrdel(cwd_t);
//	ft_arrdel(ret_t);
	return (cwd);
}

static char	*search_path(char *arg, t_envl *envl, int opts)
{
	char	*cwd;

	if (!arg) // working
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
		if (ft_strequ(arg, "-")) //working
			return (cd_oldpwd(envl));
		if (g_shell.canonic_path)
			cwd = ft_strdup(g_shell.canonic_path);
		else if (!(cwd = ft_strdup(get_env_val(envl, "PWD"))))
			cwd = getcwd(NULL, 0);
		cwd = ft_strjoin(cwd, "/"); //leaks
		cwd = ft_strjoin(cwd, arg); //leaks
	}
	else
		cwd = ft_strdup(arg);
	cwd = rework_canonic_path(cwd); //working
	if (opts)
		cwd = get_lnk_path(cwd);
	return (cwd);
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
	if (!(path = search_path(*(arg + i), envl, opts)))
		return (1);
	if (!(oldpwd = ft_strdup(get_env_val(envl, "PWD"))))
	{
		//		ft_strdel(&path);
		return (1);
	}
	if (chdir(path))
	{
		ft_putstr_fd("sh: cd: ", 2);
		ft_putstr_fd(*(arg + i), 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		//		ft_strdel(&path);
		//		ft_strdel(&oldpwd);
		return (1);
	}
	ft_strdel(&g_shell.canonic_path);
	g_shell.canonic_path = ft_strdup(path);
	printf("path = %s\n", path);
	printf("oldpath = %s\n", oldpwd);
	push_env(&g_shell.envl, "OLDPWD", oldpwd, 1);
	push_env(&g_shell.envl, "PWD", path, 1);
//	printf("pathdel\n");
	//	ft_strdel(&path);
//	printf("olddel\n");
	//	ft_strdel(&oldpwd);
//	printf("end\n");
	return (0);
}
