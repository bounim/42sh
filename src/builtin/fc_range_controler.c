/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_range_controler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 11:35:41 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/19 15:58:58 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"


static int	build_range_no_arg(int fc_range[2], int fc_opts[5], int histsize)
{
	if (fc_opts[L])
	{
		fc_range[0] = histsize - 15;
		fc_range[1] = histsize;
	}
	else
	{
		fc_range[0] = histsize;
		fc_range[1] = histsize;
	}
	return (0);
}

static int	build_range_one_arg(int fc_range[2], int fc_opts[5], int histsize, char **av)
{
	int	value;
	int arg_is_num;

	arg_is_num = check_if_arg_isdigit(av);
	if ((value = ft_atoi(*av)) <= 0)
		value = get_good_value_for_range(value, histsize);
	if (fc_opts[L])
	{
		if (arg_is_num)
			return (return_fc_error(OUT_OF_RANGE, NULL));
		fc_range[0] = value;
		fc_range[1] = histsize;
	}
	else
	{
		if (arg_is_num)
			return (return_fc_error(CMD_NOT_FOUND, *av));
		fc_range[0] = value;
		fc_range[1] = value;
	}
	return (0);
}

static int	build_range_two_arg(int fc_range[2], int fc_opts[5], int histsize, char **av)
{
	int	value1;
	int value2;
	int arg_is_num;

	if (!(arg_is_num = check_if_arg_isdigit(av)))
		arg_is_num = check_if_arg_isdigit(av + 1);
	if ((value1 = ft_atoi(*av)) <= 0)
		value1 = get_good_value_for_range(value1, histsize);
	if ((value2 = ft_atoi(*(av + 1))) <= 0)
		value2 = get_good_value_for_range(value2, histsize);
	if (arg_is_num)
	{
		if (fc_opts[L])
			return (return_fc_error(OUT_OF_RANGE, NULL));
		return (return_fc_error(CMD_NOT_FOUND, *av));
	}
	fc_range[0] = value1;
	fc_range[1] = value2;
	return (0);
}

int			build_fc_range(char **av, int fc_range[2], int fc_opts[5])
{
	int histsize;

	histsize = get_hist_full_size(g_shell.hist.history);
	if (fc_opts[E] && av)
		av++;
	if (!(*av))
		return (build_range_no_arg(fc_range, fc_opts, histsize));
	if (!*(av + 1))
		return (build_range_one_arg(fc_range, fc_opts, histsize, av));
	return (build_range_two_arg(fc_range, fc_opts, histsize, av));
}