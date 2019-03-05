/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 18:25:42 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/04 17:25:09 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int		put_setenv_error(int err)
{
	if (err == 1)
		ft_putendl_fd("setenv: Variable name must begin with a letter", 2);
	else if (err == 2)
		ft_putendl_fd("setenev: Too many arguments.", 2);
	else if (err == 3)
		ft_putendl_fd("setenv: Variable name must containt \
						alphanumeric characters.", 2);
	return (1);
}

int				built_setenv_check_error(uint8_t **arg, int *arg_size)
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
		while (i < arg_size[1])
		{
			if (!ft_isalnum(arg[1][i]))
					return (put_setenv_error(3));
			i++;
		}
	}
	return (0);
}

int				built_env_find_last_cmd(uint8_t **arg, int *arg_size)
{
	int	stock;
	int	i;

	i = 0;
	stock = 0;
	while (arg[i])
	{
		if (arg_size[i] >= 4 && ft_memcmp(arg[i], "env\0", 4))
		{
			stock = 1;
			i++;
		}
		else if (arg_size[i] >= 3 && ft_memcmp(arg[i], "-i\0", 3) && stock == 1)
		{
			stock = 1;
			i++;
		}
		else if (ft_memchr(arg[i], '=', arg_size[i]) && (stock == 1 || stock == 2))
		{
			stock = 2;
			i++;
		}
		else
			return (i);
	}
	return (i);
}


int			built_env_check_error(uint8_t **arg, int *arg_size, t_envl *head)
{
	int	i;

	i = 0;
	if (!head)
		return (ENV_ERROR);
	arg_size++;
	arg++;
/*	while (arg[i])
	{
		if (arg[i] == 
		i++;
	}*/
	return (ENV_OK);
}
