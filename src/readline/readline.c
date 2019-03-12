/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 15:57:28 by aguillot          #+#    #+#             */
/*   Updated: 2019/03/12 15:57:31 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	init_char_list(void)
{
	g_shell.edit.char_list.head = NULL;
	g_shell.edit.char_list.tail = NULL;
	g_shell.edit.char_list.char_nb = 0;
}

void	init_prompt(int prompt_id)
{
	size_t	i;

	i = 0;
	if (prompt_id == BASIC_PROMPT)
		while (BASIC_PRMPT[i])
			add_char_to_list((uint8_t *)&(BASIC_PRMPT[i++]), 1, 1);
	else if (prompt_id == QUOTE_PROMPT)
		while (QUOTE_PRMPT[i])
			add_char_to_list((uint8_t *)&(QUOTE_PRMPT[i++]), 1, 1);
	else if (prompt_id == BACKSLASH_PROMPT)
		while (BACKSLASH_PRMPT[i])
			add_char_to_list((uint8_t *)&(BACKSLASH_PRMPT[i++]), 1, 1);
	else if (prompt_id == HEREDOC_PROMPT)
		while (HEREDOC_PRMPT[i])
			add_char_to_list((uint8_t *)&(HEREDOC_PRMPT[i++]), 1, 1);
	g_shell.edit.mark = g_shell.edit.point_char;
}

int		get_term_pos(size_t *line, size_t *col)
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

void	init_edit(void)
{
	size_t 	line;
	size_t	col;

	g_shell.edit.edit_mode = MODE_EMACS;
	g_shell.edit.point_char = NULL;
	g_shell.edit.mark = NULL;
	g_shell.edit.cur_base_x = 0;
	g_shell.edit.cur_base_y = 0;
	g_shell.edit.term_info.capa = g_shell.raw_tio;
	g_shell.edit.term_info.origin = g_shell.cooked_tio;
	ioctl(STDERR_FILENO, TIOCGWINSZ, &g_shell.edit.term_info.max);
	if (get_term_pos(&line, &col) < 0)
	{
		// TODO
	}
	g_shell.edit.cur_base_x = col;
	g_shell.edit.cur_base_y = (int)line;
	g_shell.edit.cpy_buff = NULL;
}

void	readline(int prompt_id)
{
	raw_terminal();
	init_edit();
	init_char_list();
	init_prompt(prompt_id);
	print_prompt();
	input_controller();
	cooked_terminal();
}
