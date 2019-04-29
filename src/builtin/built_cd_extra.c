/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:17:23 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/15 14:54:22 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static char	**canonic_path_rework_tab(char **cwd_t, int *k, int i, int j)
{
	char	**ret;

	i = ft_arrlen(cwd_t);
	if (!(ret = (char **)malloc((i + 1) * sizeof(char *))))
		return (NULL);
	ft_memset(ret, 0, (i + 1) * sizeof(char *));
	i = 0;
	while (cwd_t[i])
	{
		if (ft_strequ(cwd_t[i], ".."))
		{
			if (j > 0)
				j--;
		}
		else if (!ft_strequ(cwd_t[i], "."))
		{
			ft_strdel(&ret[j]);
			ret[j] = ft_strdup(cwd_t[i]);
			j++;
		}
		i++;
	}
	*k = j;
	return (ret);
}

char		*rework_canonic_path(char *cwd)
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
	ft_strdel(&cwd);
	if (!(ret_t = canonic_path_rework_tab(cwd_t, &j, ft_arrlen(cwd_t), 0)))
		return (NULL);
	cwd = (j == 0) ? ft_strdup("/") : ft_strdup("");
	while (i < j)
	{
		cwd = ft_strfjoin(cwd, "/", 0);
		cwd = ft_strfjoin(cwd, ret_t[i++], 0);
	}
	ft_arrdel(cwd_t);
	ft_arrdel(ret_t);
	return (cwd);
}

static char	*check_cdpath_t(char **cdpath_t, char *arg, int opts)
{
	char		*cwd;
	int			i;
	struct stat	sb;

	cwd = NULL;
	i = 0;
	while (cdpath_t[i])
	{
		if (ft_strnequ(cdpath_t[i], ".", 1) || ft_strnequ(cdpath_t[i], "..", 2))
			cdpath_t[i] = rework_cdpath_arr(cdpath_t[i]);
		cwd = ft_strdup(cdpath_t[i]);
		cwd = ft_strfjoin(cwd, "/", 0);
		cwd = ft_strfjoin(cwd, arg, 0);
		if (lstat(cwd, &sb) == 0 || cdpath_t[i + 1] == NULL)
			return (cwd);
		ft_strdel(&cwd);
		i++;
	}
	if (!opts)
		return (NULL);
	return (ft_strdup(arg));
}

static char	*rework_last_cwd(char *cwd, char *arg, int len)
{
	if (cwd)
		return (cwd);
	if (len != 0)
		return (NULL);
	if (!(cwd = ft_strdup(g_shell.canonic_path)))
		return (NULL);
	cwd = ft_strfjoin(cwd, "/", 0);
	cwd = ft_strfjoin(cwd, arg, 0);
	return (cwd);
}

char		*find_cdpath(char *arg, t_envl *envl, int opts)
{
	char		*cdpath;
	char		**cdpath_t;
	char		*cwd;
	int			len;

	len = 0;
	cwd = NULL;
	if (ft_strnequ(arg, "/", 1) || ft_strnequ(arg, "./", 2)
			|| ft_strnequ(arg, "../", 3) || ft_strnequ(arg, ".", 1)
			|| ft_strnequ(arg, "..", 2))
		return (rework_last_cwd(cwd, arg, 0));
	if ((cdpath = get_env_val(envl, "CDPATH")))
	{
		if (!(cdpath_t = ft_strsplit(cdpath, ':')))
			return (ft_strdup(arg));
		cwd = check_cdpath_t(cdpath_t, arg, opts);
		len = ft_arrlen(cdpath_t);
		ft_arrdel(cdpath_t);
	}
	cwd = rework_last_cwd(cwd, arg, len);
	return (cwd);
}
