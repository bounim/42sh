/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 11:26:32 by schakor           #+#    #+#             */
/*   Updated: 2019/02/06 14:23:54 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

struct						s_shell
{
	const char				*prompt;
	size_t					len_prompt;
	int						sigtstp_sig;
	char					*line;
	char					**env;
	t_history				*history;
	int						history_size;
	int						history_save;
	t_envl					*envl;
	t_termios				cooked_tio;
	t_termios				raw_tio;
	t_printer_handle		out;
	t_printer_handle		err;
};

/*
**	terminal / shell functions
*/

t_shell						*singleton_shell(void);
t_shell						*init_shell(int ac, char **av, char **env);
void						run_shell(t_shell *sh);
void						init_terminal(t_shell *sh);
void						reset_terminal(t_shell *sh);
void						clean_shell(t_shell *sh);
void						fatal_exit(t_shell *sh, int code);

#endif
