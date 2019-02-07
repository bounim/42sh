/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controler_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 13:33:25 by khsadira          #+#    #+#             */
/*   Updated: 2019/02/06 16:23:53 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	rl_switch_history(t_rl *rl)
{
	t_history	*head;
	int			i;

	i = 0;
	head = rl->history;
	if (!rl->buf || rl->buf[0] == '\0')
		return ;
	while (i < rl->history_save && rl->history->bfr)
	{
		rl->history = rl->history->bfr;
		i++;
	}
	if (ft_strcmp(rl->history->buf, rl->buf) != 0)
	{
		free(rl->history->buf);
		if (!(rl->history->buf = (char *)ft_memalloc(rl->bufvar.len_tot)))
			fatal_exit(singleton_shell(), SH_ENOMEM);
		ft_memcpy(rl->history->buf, rl->buf, rl->bufvar.len_buf);
		rl->history->bufvar = rl->bufvar;
	}
	rl->history = head;
}

int		listlen(t_history *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->bfr;
	}
	return (i);
}

void	rl_print_history(t_rl *rl)
{
	rl_move_start(rl);
	ft_putstr(tgetstr("cd", NULL));
	rl_display_prompt(rl->prompt);
	free(rl->buf);
	if (!(rl->buf = (char *)ft_memalloc(rl->history->bufvar.len_tot)))
		return ;
	ft_memcpy(rl->buf, rl->history->buf, rl->history->bufvar.len_buf);
	rl->bufvar = rl->history->bufvar;
	write(1, rl->buf, rl->bufvar.len_buf);
}

void	rl_add_history(t_rl *rl)
{
	t_history	*new_ele;

	new_ele = rl_new_hist(rl->buf, rl->bufvar);
	rl->history = rl_add_hist(rl->history, new_ele);
}
