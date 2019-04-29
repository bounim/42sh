/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd_opts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:17:55 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/25 15:17:57 by khsadira         ###   ########.fr       */
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
		else if (arg[i] != 'P')
		{
			ft_putstr_fd("cd: -", 2);
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

int			cd_first_arg(char **arg, int *opts)
{
	int	i;

	*opts = 0;
	i = 1;
	while (arg[i])
	{
		if (ft_strequ(arg[i], "-"))
			return (i);
		if (ft_strequ(arg[i], "--"))
			return (i + 1);
		else if (ft_strnequ(arg[i], "-", 1))
		{
			if (cd_check_opts(arg[i], opts) == 0)
				return (0);
		}
		else
			return (i);
		i++;
	}
	return (i);
}
