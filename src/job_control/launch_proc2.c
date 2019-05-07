/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_proc2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:45:08 by emartine          #+#    #+#             */
/*   Updated: 2019/04/30 18:45:09 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int			get_return_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else if (WIFSTOPPED(status))
		return (256 + WSTOPSIG(status));
	return (1);
}

static void	update_job_status_background(t_proc *proc, int status)
{
	if (WIFSTOPPED(status))
		return ;
	proc->job->running--;
	if (proc->next)
		return ;
	if (WIFSIGNALED(status))
		g_shell.background_signal = WTERMSIG(status);
	else if (WIFEXITED(status))
		g_shell.exit_code = WEXITSTATUS(status);
}

t_proc		*update_job_status(t_job *job, pid_t wpid, int status, int silent)
{
	t_proc	*proc;

	if (!(proc = get_proc_from_job(job, wpid)) && !(proc = get_proc(wpid)))
		return (NULL);
	if (g_shell.background)
	{
		update_job_status_background(proc, status);
		return (NULL);
	}
	if (WIFSTOPPED(status))
	{
		if (proc->job->head_proc == proc || proc->job->foot_proc == proc)
		{
			proc->job->stopped = 1;
			proc->job->background = 0;
			proc->job->sig = WSTOPSIG(status);
			add_job(job);
			if (!silent)
				detailed_list(&g_shell.err, proc->job, 0, 0);
		}
	}
	else
	{
		proc->job->running--;
		if (proc->job->foot_proc == proc)
		{
			if (!proc->job->background)
				g_shell.exit_code = get_return_status(status);
			if (WIFSIGNALED(status))
			{
				proc->job->sig = WTERMSIG(status);
				if (!silent && proc->job->background)
					detailed_list(&g_shell.err, proc->job, 0, 0);
			}
			else if (WIFEXITED(status) && proc->job->background && !silent)
			{
				detailed_list(&g_shell.err, proc->job, 0,
						get_return_status(status));
			}
		}
	}
	printer_flush(&g_shell.err);
	return (proc);
}

static void	wait_job_loop(t_job *job)
{
	int		status;
	pid_t	wpid;

	status = 0;
	while (!job->stopped && job->running > 0
			&& (wpid = waitpid(WAIT_ANY, &status, WUNTRACED)) >= 0)
	{
		update_job_status(job, wpid, status, 0);
		status = 0;
	}
}

void		wait_job(t_job *job, int cont)
{
	if (!g_shell.background)
		tcsetpgrp(g_shell.term, job->pgid);
	if (cont)
	{
		job->stopped = 0;
		job->background = 0;
		tcsetattr(g_shell.term, TCSADRAIN, &job->tmodes);
		kill(-job->pgid, SIGCONT);
		g_shell.previous_job = g_shell.current_job;
		g_shell.current_job = job;
	}
	wait_job_loop(job);
	if (!g_shell.background)
	{
		tcsetpgrp(g_shell.term, g_shell.pgid);
		if (job->running > 0)
			tcgetattr(g_shell.term, &job->tmodes);
		cooked_terminal();
	}
}
