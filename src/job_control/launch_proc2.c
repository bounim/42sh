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
