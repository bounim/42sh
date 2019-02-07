/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:38:20 by schakor           #+#    #+#             */
/*   Updated: 2019/02/06 16:23:53 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void		rl_up_history_here(t_rl *rl)
{
	int			i;
	t_history	*head;

	head = rl->history;
	i = 0;
	while (i < rl->history_save && rl->history->bfr)
	{
		rl->history = rl->history->bfr;
		i++;
	}
	rl_print_history(rl);
	rl->history = head;
}

void			rl_get_prev_history(t_rl *rl)
{
	if (!rl->history)
		return ;
	rl_switch_history(rl);
	if (listlen(rl->history) == rl->history_save + 1)
		return ;
	if (!(rl->bufvar.i_buf) && (rl->history_save == -2))
		return ;
	if (rl->history_save == -2 || rl->history_save == -1)
	{
		rl_print_history(rl);
		rl->history_save = 0;
	}
	else
	{
		if (listlen(rl->history) != rl->history_save + 1)
			rl->history_save++;
		rl_up_history_here(rl);
	}
}
