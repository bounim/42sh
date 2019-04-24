/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_command_mode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:20:17 by schakor           #+#    #+#             */
/*   Updated: 2019/04/05 19:53:58 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void			vi_command_mode(void)
{
	move_left();
	g_shell.edit.edit_mode = MODE_VI_COMMAND;
}

void			invoke_vi(void)
{
	return ;
}

void			treat_as_comment(void)
{
	t_char		*tmp;
	t_char		*new;

	tmp = find_first_non_prompt(g_shell.edit.char_list.head);
	if (!(new = (t_char *)malloc(sizeof(*new))))
		fatal_exit(SH_ENOMEM);
	ft_memset(new->charac, '\0', sizeof(new->charac));
	new->charac[0] = '#';
	new->len = 1;
	if (tmp->is_prompt == TRUE)
	{
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	else
	{
		new->prev = tmp->prev;
		new->prev->next = new;
		new->next = tmp;
		tmp->prev = new;
	}
	update_all_pos();
	clean_and_print();
	return_fn();
}
