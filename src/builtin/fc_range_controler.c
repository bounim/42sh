/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_range_controler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 11:35:41 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/18 11:35:42 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int 	check_one_nb(int fc_value)
{
	int histsize;

	histsize = get_hist_full_size(g_shell.hist.history);
	if (fc_value <= histsize)
	{
		printf("IN RANGE\n");
		return (IN_RANGE);
	}
	printf("HISTSIZE: %d, fc_value: %d\n", histsize, fc_value);
	return (OUT_OF_RANGE);
}

static int	check_a_range(int fc_range[2])
{
	int histsize;
	int start;
	int last;

	start = fc_range[0];
	last = fc_range[1];
	histsize = g_shell.hist.history_size;
	if (start > histsize)
		return (OUT_OF_RANGE);
	if (start <= histsize && last >= histsize)
		return (IN_RANGE);
	if (start <= histsize && last <= histsize)
	{
		if (start <= last)
			return (IN_RANGE);
		return (OUT_OF_RANGE);
	}
	return (OUT_OF_RANGE);
}

int			check_fc_range(int fc_range[2], int range_nb)
{
	t_history 	*head;

	head = find_first_hist_line();
	if (range_nb == NO_ARG)
		return (NO_ARG);
	if (range_nb == NUMBER)
	{
		if (check_one_nb(fc_range[0]) == IN_RANGE)
			return (NUMBER);
		print_usage_fc('e');
		return (OUT_OF_RANGE);
	}
	if (range_nb == RANGE)
	{
		if (check_a_range(fc_range) == IN_RANGE)
			return (RANGE);
		print_usage_fc('e');
		return (OUT_OF_RANGE);
	}
	return (NO_ARG);
}

static int	arrange_range(int *nb, int neg, int histsize)
{
	if (!neg || *nb == 0)
		return (*nb);
	*nb *= -1;
	printf("HISTSIZE: %d, NB_AFTER_TRANSFORM: %d\n", histsize, histsize - *nb);
	return (histsize - *nb);
}

int			build_fc_range(char **av, int fc_range[2], int i)
{
	int first;
	int last;
	int histsize;
	int	neg;

	histsize = get_hist_full_size(g_shell.hist.history);
	if (!av[i])
		return (0);//ca veut dire pas de range.
	neg = (av[i][0] == '-') ? 1 : 0;
	first = ft_atoi(av[i]);
	arrange_range(&first, neg, histsize);
	i++;
	fc_range[0] = first;
	if (!av[i])
		return (NUMBER);//une seule valeur
	neg = (av[i][0] == '-') ? 1 : 0;
	last = ft_atoi(av[i]);
	arrange_range(&last, neg, histsize);
	fc_range[1] = last;
	printf("first %d, last %d\n", first, last);
	return (RANGE);//2 valeurs
}