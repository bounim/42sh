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

static void	wait_job_loop(t_proc *proc, int *status, pid_t wpid, t_proc *cur)
{
	while (proc->job->running > 0 && (wpid = waitpid(WAIT_ANY, status,
					WUNTRACED)) >= 0)
	{
		if (WIFSTOPPED(*status))
		{
			kill(wpid, SIGTERM);
			kill(wpid, SIGCONT);
			continue ;
		}
		cur = proc->job->head_proc;
		while (cur)
		{
			if (wpid == cur->pid)
			{
				proc->job->running--;
				if (!cur->next)
					g_shell.exit_code = get_return_status(*status);
				break ;
			}
			cur = cur->next;
		}
		*status = 0;
	}
}

void		wait_job(t_proc *proc)
{
	int		status;

	if (proc->next)
		return ;
	tcsetpgrp(g_shell.term, proc->job->pgid);
	status = 0;
	wait_job_loop(proc, &status, 0, NULL);
	tcsetpgrp(g_shell.term, g_shell.pgid);
	tcgetattr(g_shell.term, &proc->job->tmodes);
	cooked_terminal();
}
