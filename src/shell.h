/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 11:26:32 by schakor           #+#    #+#             */
/*   Updated: 2019/03/19 13:45:33 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

extern t_shell				g_shell;

struct						s_shell
{
	t_edit					edit;
	int					term;
	size_t 					term_set;
	uint8_t 				el_mode;
	uint8_t					*line;
	size_t					line_size;
	int					is_interactive;
	t_alias					*alias;
	t_envl					*envl;
	t_hist					hist;
	t_termios				cooked_tio;
	t_termios				raw_tio;
	t_printer				out;
	t_printer				err;
	char					*canonic_path;
	t_job					*head_job;
	pid_t					pgid;

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
