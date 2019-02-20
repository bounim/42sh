/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   down_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:37:42 by schakor           #+#    #+#             */
/*   Updated: 2019/02/06 16:23:53 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void		rl_down_history_here(t_rl *rl)
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

void			rl_get_next_history(t_rl *rl)
{
	if (!rl->history)
		return ;
	rl_switch_history(rl);
	if (rl->history_save == 0)
	{
		rl_move_start(rl);
		ft_putstr(tgetstr("cd", NULL));
		rl_display_prompt(rl->prompt);
		ft_memset(rl->buf, '\0', rl->bufvar.len_tot);
		rl->history_save = -1;
		ft_memset(&(rl->bufvar), 0, sizeof(rl->bufvar));
		return ;
	}
	if (rl->history_save == -1 || rl->history_save == -2)
		return ;
	else
	{
		rl->history_save--;
		rl_down_history_here(rl);
	}
}
