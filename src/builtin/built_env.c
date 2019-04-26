/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:27:12 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/26 14:56:51 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int		built_env_end(char **arg, size_t i, t_envl **tmp, int *options)
{
	char	*name;
	size_t	j;

	name = NULL;
	j = 0;
	while (arg[i][j] != '=')
		j++;
	if (!(name = malloc(j + 1)))
		return (-1);
	ft_memmove(name, arg[i], j);
	name[j] = '\0';
	push_env(tmp, name, ft_strchr(arg[i], '=') + 1, 1);
	*options = 0;
	return (0);
}

static int		built_env_mid(char **arg, size_t i, t_envl **tmp, int *start)
{
	int	options;

	options = 0;
	if (!ft_strcmp(arg[i], "-i") && options)
	{
		free_envl(*tmp);
		*tmp = NULL;
	}
	else if (options && !ft_strcmp(arg[i], "--"))
		options = 0;
	else if (ft_strchr(arg[i], '=') && is_valid_name(arg[i]))
	{
		if (built_env_end(arg, i, tmp, &options) == -1)
			return (-1);
	}
	else if ((!options || arg[i][0] != '-') && *start == -1)
		*start = i;
	return (0);
}

int				built_env(char **arg, t_envl *envl)
{
	t_envl	*tmp;
	size_t	i;
	int		start;

	i = 1;
	start = -1;
	tmp = dup_envl(envl);
	while (arg[i])
	{
		if (built_env_mid(arg, i, &tmp, &start) == -1)
			return (-1);
		i++;
	}
	exec_env(arg, start, tmp);
	return (0);
}
