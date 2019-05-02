/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_opts_controler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 16:33:12 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/19 15:58:04 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void	set_fc_opts_to_null(int fc_opts[5])
{
	fc_opts[E] = 0;
	fc_opts[L] = 0;
	fc_opts[N] = 0;
	fc_opts[R] = 0;
	fc_opts[S] = 0;
}

static int	set_fc_opts_to_one(char opt, int fc_opts[5])
{
	if (opt == 'e')
		fc_opts[E] = 1;
	if (opt == 'l')
		fc_opts[L] = 1;
	if (opt == 'n')
		fc_opts[N] = 1;
	if (opt == 'r')
		fc_opts[R] = 1;
	if (opt == 's')
		fc_opts[S] = 1;
	if (opt == 'e' || opt == 'l' || opt == 'n' || opt == 'r' || opt == 's')
		return (1);
	else
		return (-1);
}

int			check_fc_opts(char **av, int fc_opts[5])
{
	int i;
	int j;

	i = 1;
	j = 1;
	set_fc_opts_to_null(fc_opts);
	while (av[i] && av[i][0] == '-' && ft_strisdigit(av[i] + 1) != 0)
	{
		while (av[i][j])
		{
			if (av[i][1] == '-')
				return (i + 1);
			if (set_fc_opts_to_one(av[i][j], fc_opts) == -1)
			{
				print_usage_fc(av[i][j]);
				return (-1);
			}
			j++;
		}
		j = 1;
		i++;
	}
	return (i);
}
