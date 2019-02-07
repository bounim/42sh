/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 10:17:34 by khsadira          #+#    #+#             */
/*   Updated: 2019/02/06 16:23:53 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int		ft_nblen(int nb)
{
	int			i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

void			rl_history_cmd(t_rl *rl)
{
	t_history	*tmp;
	int			i;
	int			len;

	i = 1;
	tmp = rl->history;
	while (tmp->bfr)
		tmp = tmp->bfr;
	while (tmp)
	{
		rl_move_start(rl);
		len = 5 - ft_nblen(i);
		while (len--)
			ft_putchar(' ');
		ft_putnbr(i);
		ft_putstr("  ");
		ft_putstr(tmp->buf);
		if (tmp->next)
			ft_putchar(10);
		i++;
		tmp = tmp->next;
	}
	ft_putchar('\n');
}
