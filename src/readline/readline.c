/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 15:57:28 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/26 14:18:14 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void		init_char_list(void)
{
	g_shell.edit.char_list.head = NULL;
	g_shell.edit.char_list.tail = NULL;
	g_shell.edit.char_list.char_nb = 0;
}

void		init_edit(void)
{
	size_t	line;
	size_t	col;

	g_shell.edit.reading = TRUE;
	g_shell.edit.ret_ctrl_c = FALSE;
	g_shell.edit.edit_mode = g_shell.el_mode;
	g_shell.edit.prompt_id = 0;
	g_shell.edit.point_char = NULL;
	g_shell.edit.mark = NULL;
	g_shell.edit.last_command = NULL;
	g_shell.edit.cur_base_x = 0;
	g_shell.edit.cur_base_y = 0;
	g_shell.edit.lines_to_shift = 0;
	ioctl(STDERR_FILENO, TIOCGWINSZ, &g_shell.edit.term_info.max);
	if (get_term_pos(&line, &col) < 0)
		fatal_exit(SH_EINVAL);
	g_shell.edit.cur_base_x = col;
	g_shell.edit.cur_base_y = (int)line;
	g_shell.edit.cpy_buff = NULL;
	g_shell.edit.vi_last_search_fn = -1;
	g_shell.edit.vi_last_search_char = 0;
}

void		readline(int prompt_id)
{
	uint8_t *prompt;

	raw_terminal();
	init_edit();
	init_char_list();
	if (g_shell.edit.cur_base_x != 0)
	{
		g_shell.edit.cur_base_x = 0;
		g_shell.edit.cur_base_y++;
	}
	init_prompt(prompt_id);
	prompt = prompt_to_buff(&g_shell.edit.char_list);
	print_prompt(prompt, ft_ustrlen(prompt));
	free(prompt);
	input_controller();
	cooked_terminal();
}
