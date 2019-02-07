/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_termcaps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 22:37:56 by schakor           #+#    #+#             */
/*   Updated: 2019/01/30 15:32:14 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void			rl_move_start(t_rl *rl)
{
	size_t		index;

	index = rl->bufvar.len_char + rl->len_prompt;
	while (index > 0)
	{
		ft_putstr(tgetstr("le", NULL));
		index--;
	}
}
