/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 11:44:16 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/04 14:45:29 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	launch_proc(t_proc *proc, pid_t pgid, int foreground, int in_file, int out_file)
{
	pid_t	pid;

	if (g_shell.is_interactive)
	{
		pid = getpid();
		if (pgid == 0)
			pgid = pid;
		setpgid(pid, pgid);
		if (foreground)
			my_tcsetpgrp(g_shell.term, pgid);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		signal(SIGCHLD, SIG_DFL);
	}
	if (in_file != STDIN_FILENO)
	{
		dup2(in_file, STDIN_FILENO);
		close(in_file);
	}
	if (out_file != STDOUT_FILENO)
	{
		dup2(out_file, STDOUT_FILENO);
		close(out_file);
	}
	execve(proc->path, proc->arg, proc->env);
	fatal_exit(7);
}

void	launch_job(t_job *job, int foreground)
{
	t_proc	*proc;
	pid_t	pid;
	int		my_pipe[2];
	int		in_file;
	int		out_file;

	in_file = STDIN_FILENO;
	proc = job->head_proc;
	while (proc)
	{
		if (proc->next)
		{
			if (pipe(my_pipe) < 0)	
			{
				ft_putstr_fd("pipe failed\n", 2);
				return ;
			}
			out_file = my_pipe[1];
		}
		else
			out_file = STDOUT_FILENO;
		pid = fork();
		if (pid == 0)
			launch_proc(proc, job->pgid, foreground, in_file, out_file);
		else if (pid < 0)
		{
			ft_putstr_fd("fork failed\n", 2);
			return ;
		}
		else
		{
			proc->pid = pid;
			if (g_shell.is_interactive)
			{
				if (!job->pgid)
					job->pgid = pid;
				setpgid(pid, job->pgid);
			}
		}
		if (in_file != STDIN_FILENO)
			close(in_file);
		if (out_file != STDOUT_FILENO)
			close(out_file);
		in_file = my_pipe[0];
		proc = proc->next;
	}
	format_job_info(job, "launched");
	if (!g_shell.is_interactive)
		wait_for_job(job);
	else if (foreground)
		put_in_foreground(job, 0);
	else
		put_in_background(job, 0);
}
