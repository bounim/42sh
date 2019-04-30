/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 16:47:19 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/24 13:51:17 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

# include <limits.h>
# include "twenty_one_sh.h"
# include "lexer.h"
# include "execution.h"

struct			s_proc
{
	char			**arg;
	t_envl			*envl;
	char			**env;
	char			path[PATH_MAX + 1];
	pid_t			pid;
	int				stopped;
	int				status;
	int				std_in;
	int				std_out;
	int				tunnel[2];
	int				is_fork;
	int				is_builtin;
	int				error;
	int				find_error;
	t_lexer_token	*cmd;
	struct s_proc	*prev;
	struct s_proc	*next;
	struct s_job	*job;
};

struct			s_job
{
	int				status;
	char			*cmd;
	t_proc			*head_proc;
	t_proc			*foot_proc;
	pid_t			pgid;
	t_termios		tmodes;
	struct s_job	*next;
	int				running;
};

t_job			*find_job(pid_t pgid);
int				job_is_stopped(t_job *job);
int				job_is_completed(t_job *job);
void			put_in_foreground(t_job *job, int cont);
void			put_in_background(t_job *job, int cont);
void			launch_proc(t_proc *proc);
void			launch_job(t_job *job);
int				mark_proc_status(pid_t pid, int status);
void			wait_for_job(t_job *job);
void			update_status(void);
void			format_job_info(t_job *job, const char *status);
void			job_notif(void);
void			mark_job_as_running(t_job *job);
t_job			*init_job(void);
t_proc			*init_proc(void);
t_job			*create_job(t_lexer_token *cmd);
t_proc			*create_proc(t_job **job, t_lexer_token *cmd);
t_job			*add_job(t_job *head, t_job *new_job);
t_proc			*add_proc(t_proc *head, t_proc *new_proc);
t_job			*create_job_list(t_lexer_token *cmd);
void			free_arr(char **arr);
void			free_job(t_job *job);
void			free_proc(t_proc *proc);
void			free_exec(void);
void			wait_job(t_proc *proc);

#endif
