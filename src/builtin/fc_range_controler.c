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

int			check_fc_range(int fc_range[2])
{
	int histsize;

	histsize = get_hist_full_size(g_shell.hist.history);
	if (fc_range[0] > histsize)
	{
		print_usage_fc('e');
		return (OUT_OF_RANGE);
	}
	return (IN_RANGE);
}

static int	arrange_nb(int nb, int histsize)
{
	if (nb == -0)
		return (0);
	nb *= -1;
	printf("HISTSIZE: %d, NB_AFTER_TRANSFORM: %d\n",\
			histsize, histsize - nb + 1);
	return (histsize - nb + 1);
}

void		build_fc_range(char **av, int fc_range[2], int i)
{
	int histsize;
	int tmp;

	histsize = get_hist_full_size(g_shell.hist.history);
	if (!av[i])
	{
		fc_range[0] = histsize - 15;
		fc_range[1] = histsize;
		return ;
	}
	if ((fc_range[0] = ft_atoi(av[i])) < 0)
		fc_range[0] = arrange_nb(fc_range[0], histsize);
	if (!av[++i])
	{
		fc_range[1] = histsize;
		return ;
	}
	if ((fc_range[1] = ft_atoi(av[i])) < 0)
		fc_range[1] = arrange_nb(fc_range[0], histsize);
	if (fc_range[0] > fc_range[1])
	{
		tmp = fc_range[0];
		fc_range[0] = fc_range[1];
		fc_range[1] = tmp;
	}
}
