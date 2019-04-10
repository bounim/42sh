/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_delete_controler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:20:17 by schakor           #+#    #+#             */
/*   Updated: 2019/04/05 19:53:58 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void		vi_delete_c(void)
{

}

void		vi_delete_endline_insert_eol(void)
{
	delete_endline();
	go_to_end();
	g_shell.edit.edit_mode = MODE_VI_INSERT;
}

void		vi_clear_line_insert(void)
{
	t_char	*curr;
	t_char	*tmp;
	t_char	*prompt;

	curr = g_shell.edit.char_list.head;
	while (curr->is_prompt)
		curr = curr->next;
	prompt = curr->prev;
	while (curr)
	{
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	prompt->next = NULL;
	g_shell.edit.char_list.tail = prompt;
	g_shell.edit.point_char = g_shell.edit.char_list.tail;
	g_shell.edit.edit_mode = MODE_VI_INSERT;
	clean_and_print();
}

void					vi_delete_x(void)
{

}

void					vi_delete_bigx(void)
{

}