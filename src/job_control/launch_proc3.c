/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_proc3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 05:44:27 by emartine          #+#    #+#             */
/*   Updated: 2019/05/07 05:44:28 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

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

static void	job_stopped(t_proc *proc, int status, int silent)
{
	if (proc->job->head_proc == proc || proc->job->foot_proc == proc)
	{
		proc->job->stopped = 1;
		proc->job->background = 0;
		proc->job->sig = WSTOPSIG(status);
		add_job(proc->job);
		if (!silent)
			detailed_list(&g_shell.err, proc->job, 0, 0);
	}
}

static void	job_terminated(t_proc *proc, int status, int silent)
{
	proc->job->running--;
	if (proc->job->foot_proc == proc)
	{
		proc->job->stopped = 0;
		if (!proc->job->background)
			g_shell.exit_code = get_return_status(status);
		if (WIFSIGNALED(status))
		{
			proc->job->sig = WTERMSIG(status);
			detailed_list(&g_shell.err, proc->job, 0, 0);
		}
		else if (WIFEXITED(status) && proc->job->background && !silent)
		{
			detailed_list(&g_shell.err, proc->job, 0,
					get_return_status(status));
		}
	}
}

t_proc		*update_job_status(t_job *job, pid_t wpid, int status, int silent)
{
	t_proc	*proc;

	if (!(proc = get_proc_from_job(job, wpid))
			&& !(proc = get_proc(wpid)))
		return (NULL);
	if (g_shell.background)
	{
		update_job_status_background(proc, status);
		return (NULL);
	}
	if (WIFSTOPPED(status))
		job_stopped(proc, status, silent);
	else
		job_terminated(proc, status, silent);
	printer_flush(&g_shell.err);
	return (proc);
}
