/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:24:31 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/08 20:51:16 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	rework_canonic_path(void)
{
	int		nb_bfr;
	int		i;
	int		j;
	char	*tmp;
	char	**canonic_tab;

	j = 0;
	if (!g_shell.canonic_path)
		return ;
	tmp = g_shell.canonic_path;
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
			return ;
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
	}
	g_shell.canonic_path = tmp;
}

static char			*get_opts_path(char *arg)
{
	struct stat	buf;
	char		link[255];
	int			rl;
	char		*tmp;

	printf("laaha\n");
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

	printf("get_cd_path | %d\n", opts);
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
	else if (ft_strequ(arg, "..") && g_shell.canonic_path) //nequ
	{
		tmp = ft_strdup(g_shell.canonic_path);
		tmp = ft_strfjoin(tmp, "/..", 0);
		ft_putstr(tmp);
		ft_putchar(10);
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

	tmp = get_env_val(*env, "PWD");
	if (tmp)
		return (0);
	if (g_shell.canonic_path)
		cwd = ft_strdup(g_shell.canonic_path);
	else if (!(cwd = getcwd(NULL, 0)))
	{
		write(2, "cd: GETCWD error\n", 17);
		return (1);
	}
	push_env(env, "PWD", cwd);
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
	if (!(tmp = get_env_val(*env, "OLDPWD")))
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		return (1);
	}
	printf("%s\n", tmp);
	cwd = ft_strdup(tmp);
	rework_canonic_path();
	if (!(pwd = get_env_val(*env, "PWD")))
		pwd = g_shell.canonic_path;
	printf("pwd = %s\n", pwd);
	push_env(env, "OLDPWD", pwd);
	if (chdir(cwd) == -1)
	{
		ft_putendl_fd("cd: CHDIR error", 2);
		return (1);
	}
	push_env(env, "PWD", cwd);
	return (0);
}

static int		cd_first_arg(char **arg, int *opts)
{
	int	i;
	int	l;

	l = 0;
	i = 1;
	while (arg[i])
	{
		if (ft_strequ(arg[i], "-L"))
			l = 1;
		else if (ft_strequ(arg[i], "-P") && l == 0)
			*opts = 1;
		else if (!ft_strequ(arg[i], "-P") || !ft_strequ(arg[i], "-L") || !ft_strequ(arg[i], "--"))
			return (i);
		i++;
	}
	return (i);
}

int				built_cd(char **arg, t_envl **env)
{
	char	*path;
	char	*oldpwd;
	size_t	i;
	int		opts;

	printf("\nCD\n\n");
	i = cd_first_arg(arg, &opts);
	printf("arg[i] = %s | opts = %d\n", arg[i], opts);
	if ((oldpwd = get_env_val(*env, "PWD")))
		oldpwd = ft_strdup(oldpwd);
	else
		oldpwd = ft_strdup("");
	if (init_pwd(env))
		return (1);
	if (ft_strequ(arg[i], "-"))
		return (cd_oldpwd(env));
	if (!(path = get_cd_path(*env, arg[i], opts)))
		return (1);
	g_shell.canonic_path = ft_strdup(path);
	if (chdir(path) == -1)
	{
		ft_putendl_fd("cd: CHDIR error", 2);
		return (1);
	}
	rework_canonic_path();
	push_env(env, "OLDPWD", oldpwd);
	push_env(env, "PWD", path);
	printf("PWD = %s | OLDPWD = %s | CANONIC_PATH = %s\n", get_env_val(*env, "PWD"), get_env_val(*env, "OLDPWD"), g_shell.canonic_path);
	ft_putstr(path);
	ft_putchar(10);

	return (0);
}
