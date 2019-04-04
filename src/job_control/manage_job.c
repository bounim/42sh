/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 11:44:14 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/04 13:43:27 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

t_job	*find_job(pid_t pgid)
{
	t_job	*job;

	job = g_shell.head_job;
	while (job)
	{
		if (job->pgid == pgid)
			return (job);
		job = job->next;
	}
	return (NULL);
}

int	job_is_stop(t_job *job)
{
	t_proc	*proc;

	proc = job->head_proc;
	while (proc)
	{
		if (!proc->finish && !proc->stop)
			return (0);
		proc = proc->next;
	}
	return (1);
}

int	job_is_finish(t_job *job)
{
	t_proc	*proc;

	proc = job->head_proc;
	while (proc)
	{
		if (!proc->finish)
			return (0);
		proc = proc->next;
	}
	return (1);
}

int	my_tcsetpgrp(int fd, pid_t pgrp_id)
{
	return (ioctl(fd, TIOCSPGRP, &pgrp_id));
}

pid_t	my_tcgetpgrp (int fd)
{
	int pgrp;
	
	pgrp = 0;
	if (ioctl(fd, TIOCGPGRP, &pgrp) < 0)
		return ((pid_t)-1);
	return ((pid_t)pgrp);
}

void	free_job(t_job *job)
{
	if (job)
	{
		ft_strdel(&job->cmd);
		free_proc(job->head_proc);
		free(job);
	}
}

void	free_proc(t_proc *proc)
{
	t_proc	*tmp;
	int	i;

	tmp = proc;
	while (proc)
	{
		i = 0;
		while (proc->arg[i])
			ft_strdel(&(proc->arg[i++]));
		free(proc->arg);
		i = 0;
		while (proc->env[i])
			ft_strdel(&(proc->env[i++]));
		free(proc->env);
		tmp = proc;
		free(proc);
		proc = proc->next;
	}
}
