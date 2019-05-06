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

static uint8_t	*fill_command_edit(void)
{
	uint8_t		*cmd_edit;
	t_char		*head_char;
	t_history	*head;
	int			count;

	cmd_edit = NULL;
	count = g_shell.edit.count;
	head_char = find_first_non_prompt(g_shell.edit.char_list.head);
	if (g_shell.edit.count_exist == TRUE && count < g_shell.hist.history_size)
	{
		head = find_first_hist_line();
		cmd_edit = ft_u8_strdup((find_specific_hist_line(count, head))->buf);
	}
	else
	{
		cmd_edit = list_to_buff_print(head_char, NULL);
	}
	return (cmd_edit);
}

void			invoke_vi(void)
{
	uint8_t		*cmd_edit;

	cmd_edit = fill_command_edit();
	if (fc_modification(&cmd_edit, g_shell.envl, "vim", ft_u8_strlen(cmd_edit)) != 0)
		return ;
	free(cmd_edit);
}


