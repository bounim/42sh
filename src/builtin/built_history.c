/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:28:52 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/02 18:10:07 by khsadira         ###   ########.fr       */
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

void			built_history(t_rl rl)
{
	t_history	*tmp;
	int			i;
	int			len;

	i = 1;
	tmp = rl.history;
	while (tmp->bfr)
		tmp = tmp->bfr;
	while (tmp)
	{
		rl_move_start(&rl);
		len = 5 - ft_nblen(i);
		while (len--)
			ft_putchar(' ');
		ft_putnbr(i);
		ft_putstr("  ");
		ft_putu8str(tmp->buf);
		if (tmp->next)
			ft_putchar(10);
		i++;
		tmp = tmp->next;
	}
	ft_putchar('\n');
}
