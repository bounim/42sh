/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 11:26:32 by schakor           #+#    #+#             */
/*   Updated: 2019/03/08 16:58:27 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

extern t_shell				g_shell;

struct						s_shell
{
	size_t 					term_set;
	uint8_t 				el_mode;
	uint8_t					*line;
	t_envl					*envl;
	t_history				*history;
	int						history_size;
	int						history_save;
	t_termios				cooked_tio;
	t_termios				raw_tio;
	t_printer_handle		out;
	t_printer_handle		err;
	char					*canonic_path;
};

/*
**	terminal / shell functions
*/

void						init_shell(int ac, char **av, char **env);
void						run_shell(void);
void						raw_terminal(void);
void						cooked_terminal(void);
void						clean_shell(void);
void						fatal_exit(int code);

#endif
