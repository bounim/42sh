/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 15:57:28 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/02 18:39:53 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void		init_char_list(void)
{
	g_shell.edit.char_list.head = NULL;
	g_shell.edit.char_list.tail = NULL;
	g_shell.edit.char_list.char_nb = 0;
}

static int	get_term_pos(size_t *line, size_t *col)
{
	char	buff[32];
	size_t	n;
	int		r;

	write(1, "\033[6n", 4);
	buff[0] = '\0';
	while (buff[0] != '\033')
	{
		if (read(0, buff, 1) <= 0)
			return (-1);
	}
	if (read(0, buff, 1) <= 0 || buff[0] != '[')
		return (-1);
	n = 0;
	while (n < sizeof(buff) - 1 && (n == 0 || buff[n - 1] != ';'))
	{
		if(read (0, buff + n, 1) <= 0)
			return (-1);
		n++;
	}
	if (n == sizeof(buff) - 1)
		return (-1);
	buff[n] = '\0';
	r = atoi(buff);
	if (r < 1)
		return (-1);
	*line = (size_t)r - 1;
	n = 0;
	while (n < sizeof(buff) - 1 && (n == 0 || buff[n - 1] != 'R'))
	{
		if(read (0, buff + n, 1) <= 0)
			return (-1);
		n++;
	}
	if (n == sizeof(buff) - 1)
		return (-1);
	buff[n] = '\0';
	r = atoi(buff);
	if (r < 1)
		return (-1);
	*col = (size_t)r - 1;
	return (0);
}

void		init_edit(void)
{
	size_t	line;
	size_t	col;

	g_shell.edit.reading = TRUE;
	g_shell.edit.ret_ctrl_c = FALSE;
	g_shell.edit.edit_mode = MODE_EMACS;
	g_shell.edit.prompt_id = 0;
	g_shell.edit.point_char = NULL;
	g_shell.edit.mark = NULL;
	g_shell.edit.last_command = NULL;
	g_shell.edit.cur_base_x = 0;
	g_shell.edit.cur_base_y = 0;
	g_shell.edit.lines_to_shift = 0;
	g_shell.edit.term_info.capa = g_shell.raw_tio;
	g_shell.edit.term_info.origin = g_shell.cooked_tio;
	ioctl(STDERR_FILENO, TIOCGWINSZ, &g_shell.edit.term_info.max);
	if (get_term_pos(&line, &col) < 0)
	{
		// TODO
	}
	if (g_shell.edit_complexity == TERMCAPS_READLINE)
	{
		g_shell.edit.cur_base_x = col;
		g_shell.edit.cur_base_y = (int)line;
	}
	else
	{
		g_shell.edit.cur_base_x = 0;
		g_shell.edit.cur_base_y = 0;
	}
	g_shell.edit.cpy_buff = NULL;
}

void		readline(int prompt_id)
{
	uint8_t *prompt;

	raw_terminal();
	if (g_shell.edit_complexity == TERMCAPS_READLINE)
	{
		init_edit();
		init_char_list();
		init_prompt(prompt_id);
		prompt = prompt_to_buff(&g_shell.edit.char_list);
		print_prompt(prompt, ft_ustrlen(prompt));
		free(prompt);
		input_controller();
	}
	else
		simple_readline(prompt_id);
	cooked_terminal();
}