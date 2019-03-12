/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 11:26:32 by schakor           #+#    #+#             */
/*   Updated: 2019/03/12 16:52:57 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

extern t_shell				g_shell;

struct						s_shell
{
	t_edit					edit;
	size_t 					term_set;
	uint8_t 				el_mode;
	uint8_t					*line;
	size_t					line_size;
	t_envl					*envl;
	t_hist					hist;
	t_termios				cooked_tio;
	t_termios				raw_tio;
	t_printer				out;
	t_printer				err;
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
