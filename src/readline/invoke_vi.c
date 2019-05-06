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

static uint8_t	*fill_command_edit()
{
	uint8_t		*cmd_edit;
	t_char		*head_char;
	t_char		*tail;
	t_history	*head;
	int			count;

	count = g_shell.edit.count;
	head_char = g_shell.edit.char_list.head;
	tail = g_shell.edit.char_list.tail;
	if (g_shell.edit.count_exist == TRUE)
	{
		head = find_first_hist_line();
		cmd_edit = ft_u8_strdup(find_specific_hist_line(count, head)->buf);
	}
	else
		cmd_edit = list_to_buff_print(head_char, tail);
	return (cmd_edit);
}

void			invoke_vi(void)
{
	int			fd;
	char		path[PATH_MAX + 1];
	uint8_t		*cmd_edit;

	if (!(cmd_edit = fill_command_edit()))
		return ;
	if ((fd = random_file(path)) == -1)
		return ;
}


