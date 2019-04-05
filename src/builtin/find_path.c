/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 19:44:04 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/05 19:52:12 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

char	*find_path(char *cmd, t_envl *envl)
{
	char	**path;
	char	*fullpath;
	char	*tmp;
	size_t	i;

	if (!(path = ft_strsplit(get_env_val(envl, "PATH"), ':')))
		return (NULL);
	tmp = ft_strjoin("/", cmd);
	i = 0;
	while (path[i])
	{
		fullpath = ft_strjoin(path[i], tmp);
		if (access(fullpath, F_OK) == 0)
		{
			ft_arrdel(path);
			ft_strdel(&tmp);
			return (fullpath);
		}
		ft_strdel(&fullpath);
		i++;
	}
	ft_arrdel(path);
	ft_strdel(&tmp);
	return (NULL);
}
