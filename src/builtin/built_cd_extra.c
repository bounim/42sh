/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:17:23 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/10 18:41:26 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static char	**canonic_path_rework_tab(char **cwd_t, int *k)
{
	char	**ret;
	int		i;
	int		j;

	j = 0;
	i = ft_arrlen(cwd_t);
	if (!(ret = (char **)malloc(sizeof(char *) * i + 1)))
		return (NULL);
	while (j < i + 1)
		ret[j++] = NULL;
	j = 0;
	i = 0;
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
	if (!(ret_t = canonic_path_rework_tab(cwd_t, &j)))
		return (NULL);
	ft_strdel(&cwd);
	if (j == 0)
		cwd = ft_strdup("/");
	else
		cwd = ft_strdup("");
	while (i < j)
	{
		cwd = ft_strfjoin(cwd, "/", 0);
		cwd = ft_strfjoin(cwd, ret_t[i++], 0);
	}
	ft_arrdel(cwd_t);
	ft_arrdel(ret_t);
	return (cwd);
}
