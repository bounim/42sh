/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_moving_ctrl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 17:23:14 by schakor           #+#    #+#             */
/*   Updated: 2019/02/01 18:54:04 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void				rl_beg_of_line(t_rl *rl)
{
	while (rl->bufvar.i_char != 0)
		rl_backward_char(rl);
}

void				rl_end_of_line(t_rl *rl)
{
	while (rl->bufvar.i_char < rl->bufvar.len_char)
		rl_forward_char(rl);
}

void				rl_ctrl_x_x(t_rl *rl)
{
	(void)rl;
}

void				rl_backward_char(t_rl *rl)
{
	size_t			i;

	i = rl->bufvar.i_buf;
	if (rl->bufvar.i_char > 0)
	{
		rl->bufvar.i_char--;
		i--;
		while ((rl->buf[i] & (1 << 7) && !(rl->buf[i] & (1 << 6))))
			i--;
		ft_putstr(tgetstr("le", NULL));
		rl->bufvar.i_buf = i;
	}
}

void				rl_forward_char(t_rl *rl)
{
	size_t			i;
	struct winsize	w;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
	if (rl->bufvar.i_char >= rl->bufvar.len_char)
		return ;
	if (rl->bufvar.i_char != 0 &&
	((rl->bufvar.i_char + rl->len_prompt + 1) % w.ws_col == 0))
	{
		ft_putstr(tgetstr("cr", NULL));
		ft_putstr(tgetstr("do", NULL));
	}
	else
		ft_putstr(tgetstr("nd", NULL));
	rl->bufvar.i_char++;
	i = ++rl->bufvar.i_buf;
	if (!(rl->buf[i] & (1 << 7)))
		return ;
	while ((rl->buf[i] & (1 << 7) && !(rl->buf[i] & (1 << 6))))
		i++;
	rl->bufvar.i_buf = i;
}
