/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 19:25:02 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/30 18:17:45 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"
/*
   static char	*cd_work_path(char **arg_t, char **cwd_t)
   {
   int		i;
   int		j;
   int		stock;
   char	*ret;

   i = 0;
   if (!arg_t)
   return (NULL);
   while (ft_strequ(arg_t[i], ".."))
   i++;
   j = 0;
   ret = ft_strdup("");
   stock = ft_arrlen(cwd_t) - i;
   while (j < stock && cwd_t[j])
   {
   ret = ft_strfjoin(ret, "/", 0);
   ret = ft_strfjoin(ret, cwd_t[j], 0);
   j++;
   }
   while (arg_t[i])
   {
   ret = ft_strfjoin(ret, "/", 0);
   ret = ft_strfjoin(ret, arg_t[i], 0);
   i++;
   }
   if (!ret || !ft_strlen(ret))
   ret = ft_strdup("/");
   ft_arrdel(arg_t);
   ft_arrdel(cwd_t);
   return (ret);
   }*/
/*
   static char	*rework_path(char *arg, t_envl *envl)
   {
   char	*cwd;

   if (g_shell.canonic_path)
   cwd = ft_strdup(g_shell.canonic_path);
   else if (!(cwd = ft_strdup(get_env_val(envl, "PWD"))))
   {
   if (!(cwd = getcwd(NULL, 0)))
   {
   ft_putendl_fd("cd: cwd not found\n", 2);
   return (NULL);
   }
   }
   if (!cwd)
   return (NULL);
   return (cd_work_path(ft_strsplit(arg, '/'), ft_strsplit(cwd, '/')));
   }*/

static char	*cd_oldpwd(t_envl *envl)
{
	char	*tmp;

	if (!(tmp = ft_strdup(get_env_val(envl, "OLDPWD"))))
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		return (NULL);
	}
	return (tmp);
}
/*
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
   tmp = ft_strdup(link);
   return (tmp);
   }*/
/*
   static char	*rework_arg(char *arg, t_envl *envl)
   {
   char	*bfr;
   char	*ret;

   if (ft_strnequ(arg, "/", 1))
   return (arg);
   bfr = NULL;
   if (g_shell.canonic_path)
   bfr = ft_strdup(g_shell.canonic_path);
   else if (!(bfr = ft_strdup(get_env_val(envl, "PWD"))))
   bfr = getcwd(NULL, 0);
   if (bfr[ft_strlen(bfr) - 1] != '/')
   bfr = ft_strfjoin(bfr, "/", 0);
   ret = ft_strfjoin(bfr, arg, 0);
   return (ret);
   }*/
/*
   static char	*work_path(char *arg, int opts, t_envl *envl)
   {
   char	*lnk;
   char	*ret;

   arg = rework_arg(arg, envl);
   lnk = NULL;
   if (opts == 1)
   lnk = get_lnk_path(arg);
   if (lnk)
   {
   ret = ft_strdup("/");
   return (ret = ft_strfjoin(ret, lnk, 2));
   }
   return (ft_strdup(arg));
   }*/
/*
   static char	*cd_current_path(t_envl *envl)
   {
   char	*ret;

   if (g_shell.canonic_path)
   return (ft_strdup(g_shell.canonic_path));
   else if ((ret = ft_strdup(get_env_val(envl, "PWD"))))
   return (ret);
   else
   return (getcwd(NULL, 0));

   }*/
/*
   static char	*search_path(char *arg, t_envl *envl, int opts)
   {
   char	*ret;

   printf("arg = %s\n", arg);
   ret = NULL;
   if (!arg) // working
   {
   if (!(ret = ft_strdup(get_env_val(envl, "HOME"))))
   {
   ft_putendl_fd("cd: HOME not set", 2);
   return (NULL);
   }
   return (ret);
   }
   else if (ft_strequ(arg, "."))
   return (cd_current_path(envl));
   else if (ft_strequ(arg, "-")) //working
   return (cd_oldpwd(envl));
   else if (ft_strnequ(arg, "../", 3) || ft_strequ(arg, "..")) // working
   return (rework_path(arg, envl));
   else
   return (work_path(arg, opts, envl));
   }*/

static char	*rework_canonic_path(char *cwd)
{
	char	**cwd_t;
	char	**ret_t;
	int		i;
	int		j;

	printf("cwd = %s\n", cwd);
	if (!(cwd_t = ft_strsplit(cwd, '/')))
	{
		ft_strdel(&cwd);
		return (NULL);
	}
	i = ft_arrlen(cwd_t);
	if (!(ret_t = (char **)malloc(sizeof(char *) * i + 1)))
		return (NULL);
	j = 0;
	while (j < i)
		ret_t[j++] = NULL;
	i = 0;
	while (cwd_t[i])
	{
		if (ft_strequ(cwd_t[i], ".."))
		{
			if (j > 0)
				j--;
			i++;
		}
		else if (!ft_strequ(cwd_t[i], "."))
			ret_t[j++] = ft_strdup(cwd_t[i++]);
	}
	i = 0;
	printf("ret = %s\n", ret_t[j]);
	cwd = ft_strdup("");
	while (i < j)
	{
		printf("%s\n", ret_t[i]);
		cwd = ft_strjoin(cwd, "/");
		cwd = ft_strjoin(cwd, ret_t[i]);
		i++;
	}
	printf("end = %s\n", cwd);
	ft_arrdel(cwd_t);
	printf("end = tru\n");
	ft_arrdel(ret_t);
	printf("end =aover\n");
	return (cwd);
}

static char	*search_path(char *arg, t_envl *envl)
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
		cwd = ft_strfjoin(cwd, "/", 0);
		cwd = ft_strfjoin(cwd, arg, 0);
	}
	else
		cwd = ft_strdup(arg);
	cwd = rework_canonic_path(cwd);
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
	if (!(path = search_path(*(arg + i), envl)))
		return (1);
	if (!(oldpwd = ft_strdup(get_env_val(envl, "PWD"))))
	{
		ft_strdel(&path);
		return (1);
	}
	if (chdir(path))
	{
		ft_strdel(&path);
		ft_strdel(&oldpwd);
		return (1);
	}
	if (g_shell.canonic_path)
		ft_strdel(&g_shell.canonic_path);
	g_shell.canonic_path = ft_strdup(path);
	printf("path = %s\n", path);
	printf("oldpath = %s\n", oldpwd);
	push_env(&g_shell.envl, "OLDPWD", oldpwd, 1);
	push_env(&g_shell.envl, "PWD", path, 1);
	printf("pathdel\n");
	ft_strdel(&path);
	printf("olddel\n");
	ft_strdel(&oldpwd);
	printf("end\n");
	return (0);
}
