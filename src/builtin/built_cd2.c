/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 19:25:02 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/29 19:39:08 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	cd_check_opts(char *arg, int *opts)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] == 'P' && *opts != 2)
			*opts = 1;
		else if (arg[i] == 'L')
			*opts = 2;
		else
		{
			ft_putstr_fd("sh: cd: -", 2);
			write(2, arg + i, 1);
			ft_putstr_fd(": invalid option\ncd: usage: cd [-L|-P] [dir]\n", 2);
			return (0);
		}
		i++;
	}
	if (*opts == 2)
		*opts = 0;
	return (i);
}

static int	cd_first_arg(char **arg, int *opts)
{
	int	i;
	int	j;
	int	l;

	l = 0;
	i = 1;
	while (arg[i])
	{
		if (ft_strequ(arg[i], "-"))
			return (i);
		if (ft-strequ(arg[i], "--"))
			return (i + 1);
		else if (ft_strnequ(arg[i], "-", 1))
		{
			if (cd_check_opts(arg[i], opts))
				return (0);
		}
		else
			return (i);
		i++;
	}
	return (i);
}

int	built_cd2(char **arg, t_envl *envl)
{
	char	*path;
	char	*oldpwd;
	size_t	i;
	int		opts;

	opts = 0;
	if (!(i = cd_first_arg(arg, &opts)))
		return (1);
}
