/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 11:26:32 by schakor           #+#    #+#             */
/*   Updated: 2019/04/22 15:36:49 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

extern t_shell				g_shell;

struct						s_shell
{
	t_edit					edit;
	int						term;
	size_t					term_set;
	uint8_t					el_mode;
	uint8_t					*line;
	size_t					line_size;
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
	int						debug_mode;
	char					pid_buffer[20];
	int						exit_code;
	char					exit_buffer[10];
	t_hashmap				hmap;
	int						is_exiting;
	t_lexer					*lexer;
	char					*progname;
};

/*
**	terminal / shell functions
*/

void						init_shell(int ac, char **av, char **env);
void						run_shell(void);
void						raw_terminal(void);
void						cooked_terminal(void);
int							get_return_status(int status);
void						clean_shell(void);
void						fatal_exit(int code);

#endif
