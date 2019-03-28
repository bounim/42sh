/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_typedefs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 11:27:19 by schakor           #+#    #+#             */
/*   Updated: 2019/03/28 14:16:01 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_TYPEDEFS_H
# define SH_TYPEDEFS_H

/*
**	typedefs header for the 42sh
*/

typedef unsigned char			t_bool;
typedef struct s_edit			t_edit;
typedef struct passwd			t_passwd;
typedef struct termios			t_termios;
typedef struct s_shell			t_shell;
typedef struct s_alias			t_alias;
typedef struct s_envl			t_envl;
typedef struct s_history		t_history;
typedef struct s_char			t_char;
typedef struct s_char_list		t_char_list;
typedef struct s_keymap			t_keymap;
typedef struct s_term			t_term;
typedef struct s_hist			t_hist;
typedef struct s_opts			t_opts;
typedef struct s_opt_jobs		t_opt_jobs;
typedef struct s_proc			t_proc;
typedef struct s_job			t_job;
typedef struct s_last_command	t_last_command;

#endif
