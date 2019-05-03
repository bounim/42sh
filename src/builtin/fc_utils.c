/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 21:23:57 by aguillot          #+#    #+#             */
/*   Updated: 2019/05/03 21:23:58 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int	return_fc_error(int fc_err_code, char *av)
{
	if (fc_err_code == OUT_OF_RANGE)
		write_error("fc", "history specification out of range");
	else if (fc_err_code == CMD_NOT_FOUND)
		write_error(av, "command not found");
	return (1);
}

int			check_fc_range(int fc_range[2])
{
	int histsize;

	histsize = get_hist_full_size(g_shell.hist.history);
	if (fc_range[0] > histsize)
	{
		return(return_fc_error(OUT_OF_RANGE, NULL));
	}
	return (IN_RANGE);
}

int	check_if_arg_isdigit(char **av)
{
	if (*av[0] == '-')
		av++;
	if (ft_strisdigit(*av))
		return (1);
	return (0);
}

int 	get_good_value_for_range(int value, int histsize)
{
	if (value == 0)
		return (histsize);
	return (histsize + value);
}