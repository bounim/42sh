#include "twenty_one_sh.h"

void	launch_proc(t_proc *proc, pid_t pgid, int infile, int outfile, int errfile, int foreground)
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
	if (infile != STDIN_FILENO)
	{
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	if (outfile != STDOUT_FILENO)
	{
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	if (errfile != STDOUT_FILENO)
	{
		dup2(errfile, STDERR_FILENO);
		close(errfile);
	}
	(void)proc;
	execve(proc->path, proc->arg, proc->env);
	ft_putstr_fd("execve\n", 2);
	exit(1);
}

void	launch_job(t_job *job, int foreground)
{
	t_proc	*proc;
	pid_t	pid;
	int	my_pipe[2];
	int	outfile;
	int	infile;

	infile = job->std_in;
	proc = job->head_proc;
	while (proc)
	{
		if (proc->next)
		{
			if (pipe(my_pipe) < 0)	
			{
				ft_putstr_fd("pipe failed\n", 2);
				exit(1);
			}
			outfile = my_pipe[1];
		}
		else
			outfile = job->std_out;
		pid = fork();
		if (pid == 0)
			launch_proc(proc, job->pgid, infile, outfile, job->std_err, foreground);
		else if (pid < 0)
		{
			ft_putstr_fd("fork failed\n", 2);
			exit(1);
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
		if (infile != job->std_in)
			close(infile);
		if (outfile != job->std_out)
			close(outfile);
		infile = my_pipe[0];
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
