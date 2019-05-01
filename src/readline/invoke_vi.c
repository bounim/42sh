/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invoke_vi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:20:17 by schakor           #+#    #+#             */
/*   Updated: 2019/04/05 19:53:58 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void			invoke_vi(void)
{
	int			count;
	uint8_t 	*cmd_edit;
	t_history	*head;

	count = g_shell.edit.count;
	if (g_shell.edit.count_exist == TRUE)
	{
		head = find_first_hist_line();
		cmd_edit = find_specific_hist_line(count, head)->buf;
	}
	else
	{
		cmd_edit = list_to_buff_print(g_shell.edit.char_list.head, g_shell.edit.char_list.tail);

	}
}


