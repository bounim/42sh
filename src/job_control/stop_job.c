#include "twenty_one_sh.h"

int	mark_proc_status(pid_t pid, int status)
{
	t_job *job;
	t_proc *proc;

	if (pid > 0)
	{
		job = g_shell.head_job;
		while (job)
		{
			proc = job->head_proc;
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
						return (0);
					}
				}
				proc = proc->next;
			}
			job = job->next;
		}
		ft_putstr_fd("No child process", 2);
		ft_putnbr_fd((int)pid, 2);
		write(2, ".\n", 2);
		return (-1);
	}
	else if (pid == 0)
		return (-1);
	else
	{
		ft_putstr_fd("wait pid\n", 2);
		return (-1);
	}
}

void	wait_for_job(t_job *job)
{
	int	status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	while (!mark_proc_status(pid, status) && !job_is_stop(job) && !job_is_finish(job))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
}

void	update_status(void)
{
	int	status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	while (!mark_proc_status(pid, status))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
}

void	format_job_info(t_job *job, const char *status)
{
	ft_putnbr_fd((int)job->pgid, 2);
	ft_putstr_fd(" ", 2);
	ft_putstr_fd(status, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(job->cmd, 2);
	write(2, "\n", 1);
}

void	job_notif(void)
{
	t_job	*job;
	t_job	*last_job;
	t_job	*next_job;

	update_status();
	last_job = NULL;
	job = g_shell.head_job;
	while (job)
	{
		next_job = job->next;
		if (job_is_finish(job))
		{
			format_job_info(job, "completed");
			if (last_job)
				last_job->next = job->next;
			else
				last_job = g_shell.head_job;
			free_job(job);
			job = job->next;
		}
		else if (job_is_stop(job) && !job->notified)
		{
			format_job_info(job, "stopped");
			job->notified = 1;
			last_job = job;
		}
		else
			last_job = job;
	}
}
