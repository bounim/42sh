/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 16:47:19 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/05 19:39:57 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

struct			s_proc
{
	char			**arg;
	char			**env;
	char			*path;
	pid_t			pid;
	char			finish;
	char			stop;
	int				status;
	int				std_in;
	int				std_out;
	int				my_pipe[2];
	int				is_fork;
	int				is_builtin;
	struct s_proc	*next;
};

struct			s_job
{
	int				status;
	char			*cmd;
	t_proc			*head_proc;
	pid_t			pgid;
	char			notified;
	t_termios		tmodes;
	struct s_job	*next;
};

t_job			*find_job(pid_t pgid);
int				job_is_stop(t_job *job);
int				job_is_finish(t_job *job);
void			put_in_foreground(t_job *job, int cont);
void			put_in_background(t_job *job, int cont);
void			launch_proc(t_proc *proc, pid_t pgid,
						int foreground, int std_file[2]);
void			launch_job(t_job *job, int foreground);
int				mark_proc_status(pid_t pid, int status);
void			wait_for_job(t_job *job);
void			update_status(void);
void			format_job_info(t_job *job, const char *status);
void			job_notif(void);
void			mark_job_as_running(t_job *job);
void			continue_job(t_job *job, int foreground);
void			free_job(t_job *job);
void			free_proc(t_proc *proc);
t_job			*init_job(t_job *job);
t_proc			*init_proc(t_proc *proc);
t_job			*creat_job(char *cmd);
t_proc			*creat_proc(char **arg, t_envl *envl, char *path);
t_job			*add_job(t_job *head, t_job *new_job);
t_proc			*add_proc(t_proc *head, t_proc *new_proc);
t_job			*creat_job_list(char **arg);

#endif
