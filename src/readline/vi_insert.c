/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:16:41 by schakor           #+#    #+#             */
/*   Updated: 2019/04/10 15:05:24 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void		vi_append_mode(void)
{
	move_right();
	g_shell.edit.edit_mode = MODE_VI_INSERT;
}

void		vi_append_eol(void)
{
	go_to_end();
	g_shell.edit.edit_mode = MODE_VI_INSERT;
}

void		vi_insert_mode(void)
{
	g_shell.edit.edit_mode = MODE_VI_INSERT;
}

void		vi_insert_bol(void)
{
	go_to_home();
	g_shell.edit.edit_mode = MODE_VI_INSERT;
}

void		vi_replace_char(void)
{
	int		count;
	char	c;
	t_char	*curr;

	if (read(STDIN_FILENO, &c, 1) < 0)
		fatal_exit(SH_EINVAL);
	count = g_shell.edit.count;
	curr = g_shell.edit.point_char->next;
	if (!ft_isalnum(c) || !curr)
		return ;
	while (curr && count--)
	{
		ft_memset(curr->charac, '\0', 6);
		curr->charac[0] = (uint8_t)c;
		if (count == 0 || !curr->next)
			break ;
		curr = curr->next;
	}
	clean_and_print();
	ft_putstr(tgoto(tgetstr("cm", NULL), curr->x_pos, curr->y_pos));
	g_shell.edit.point_char = curr->prev;
}
