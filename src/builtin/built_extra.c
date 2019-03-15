/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:39:07 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/15 11:45:12 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int		put_setenv_error(int err)
{
	if (err == 1)
		ft_putendl_fd("setenv: Variable name must begin with a letter", 2);
	else if (err == 2)
		ft_putendl_fd("setenv: Too many arguments.", 2);
	else if (err == 3)
		ft_putendl_fd("setenv: Variable name must containt \
						alphanumeric characters.", 2);
	return (1);
}

int				built_setenv_check_error(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	if (i > 3)
		return (put_setenv_error(2));
	else if (arg[1])
	{
		i = 0;
		if (!ft_isalpha(arg[1][0]))
				return (put_setenv_error(1));
		while (arg[1][i])
		{
			if (!ft_isalnum(arg[1][i]))
					return (put_setenv_error(3));
			i++;
		}
	}
	return (0);
}

int				built_env_find_last_cmd(char **arg)
{
	int	stock;
	int	i;

	i = 0;
	stock = 0;
	while (arg[i])
	{
		if (ft_strequ(arg[i], "env"))
		{
			stock = 1;
			i++;
		}
		else if (ft_strequ(arg[i], "-i") && stock == 1)
		{
			stock = 1;
			i++;
		}
		else if (ft_memchr(arg[i], '=', ft_strlen(arg[i])) && (stock == 1 || stock == 2))
		{
			stock = 2;
			i++;
		}
		else
			return (i);
	}
	return (i);
}
