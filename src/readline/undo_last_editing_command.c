/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_last_editing_command.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:47:15 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/04 14:56:26 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	replace_char_list(t_last_command *last_command)
{
	uint8_t *buff;
	int		i;
	size_t	len;

	buff = last_command->buff;
	init_prompt(g_shell.edit.prompt_id);
	i = get_prompt_len(g_shell.edit.prompt_id);
	if (g_shell.edit.cur_base_y < 0)
	{
		g_shell.edit.cur_base_y = 0;
		g_shell.edit.cur_base_x = 0;
	}
	while (buff[i])
	{
		len = ft_wchar_len(buff + i);
		add_char_to_list(buff + i, len, 0);
		i += len;
	}
}

void	delete_last_command(t_last_command *last)
{
	g_shell.edit.last_command = last->prev;
	free(last->buff);
	free(last);
	last = NULL;
}

int		check_if_undo_doable(t_last_command *last)
{
	if (!last)
		return (-1);
	return (1);
}

void	undo_last_edit_command(void)
{
	if (check_if_undo_doable(g_shell.edit.last_command) == -1)
		return ;
	rl_free_controler(FREE_ONLY_EDIT_CHAR_LIST);
	init_char_list();
	replace_char_list(g_shell.edit.last_command);
	delete_last_command(g_shell.edit.last_command);
	clean_and_print();
}
