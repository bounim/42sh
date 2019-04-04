/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 11:44:04 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/04 16:30:01 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static t_proc	*mark_proc_status_next(t_proc *proc, pid_t pid,
										int *ret, int status)
{
	*ret = 0;
	while (proc)
	{
		if (proc->pid == pid)
		{
			proc->status = status;
			if (WIFSTOPPED(status))
				proc->stop = 1;
			else
			{
				proc->finish = 1;
				if (WIFSIGNALED(status))
				{
					ft_putnbr_fd((int)pid, 2);
					ft_putstr_fd(": Terminated by signal", 2);
					ft_putnbr_fd(WTERMSIG(proc->status), 2);
					write(2, ".\n", 2);
				}
				*ret = 1;
				return (proc);
			}
		}
		proc = proc->next;
	}
	return (proc);
}

static int		print_proc_child_err(pid_t pid)
{
	ft_putstr_fd("No child process", 2);
	ft_putnbr_fd((int)pid, 2);
	write(2, ".\n", 2);
	return (-1);
}

int				mark_proc_status(pid_t pid, int status)
{
	t_job	*job;
	t_proc	*proc;
	int		ret;

	if (pid > 0)
	{
		job = g_shell.head_job;
		while (job)
		{
			proc = job->head_proc;
			proc = mark_proc_status_next(proc, pid, &ret, status);
			if (ret)
				return (0);
			job = job->next;
		}
		return (print_proc_child_err(pid));
	}
	else if (pid == 0)
		return (-1);
	else
	{
		ft_putstr_fd("wait pid\n", 2);
		return (-1);
	}
}

void			wait_for_job(t_job *job)
{
	int		status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	while (!mark_proc_status(pid, status) &&
			!job_is_stop(job) && !job_is_finish(job))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
}

void			update_status(void)
{
	int		status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	while (!mark_proc_status(pid, status))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
}
