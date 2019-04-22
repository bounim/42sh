/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 12:12:34 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/04 15:08:09 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int			get_hist_full_size(t_history *tail)
{
	int ret;

	ret = 0;
	if (!tail)
		return (0);
	while (tail->next)
		tail = tail->next;
	while (tail)
	{
		ret++;
		tail = tail->bfr;
	}
	return (ret);
}

void		resize_history(t_history *hist)
{
	t_history	*tmp;
	int			stock;
	int			max;

	tmp = hist;
	stock = g_shell.hist.history_size;
	if ((max = ft_atoi(get_env_val(g_shell.envl, "HISTSIZE")))
			<= 0 || max > 50000)
		max = 50000;
	if (stock > max)
	{
		stock = max;
		while (max-- && tmp->bfr)
			tmp = tmp->bfr;
		if (tmp->next)
			(tmp->next)->bfr = NULL;
		tmp->next = NULL;
		free_history(tmp);
		g_shell.hist.history_size = stock;
	}
}
