/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 21:31:19 by emartine          #+#    #+#             */
/*   Updated: 2019/05/03 21:31:20 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

t_job			*get_job(pid_t pgid)
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

t_proc			*get_proc(pid_t pid)
{
	t_job	*job;
	t_proc	*proc;

	job = g_shell.head_job;
	while (job)
	{
		proc = job->head_proc;
		while (proc)
		{
			if (proc->pid == pid)
				return (proc);
			proc = proc->next;
		}
		job = job->next;
	}
	return (NULL);
}

t_proc			*get_proc_from_job(t_job *job, pid_t pid)
{
	t_proc	*proc;

	if (!job)
		return (NULL);
	proc = job->head_proc;
	while (proc)
	{
		if (proc->pid == pid)
			return (proc);
		proc = proc->next;
	}
	return (NULL);
}

static t_job	*get_job_by_id_end(char *id)
{
	t_job	*job;

	if (id[1] == '?')
	{
		job = g_shell.head_job;
		while (job)
		{
			if (job->cmd && ft_strstart(job->cmd, id + 2))
				return (job);
			job = job->next;
		}
	}
	else
	{
		job = g_shell.head_job;
		while (job)
		{
			if (job->cmd && ft_strstr(job->cmd, id + 2))
				return (job);
			job = job->next;
		}
	}
	return (NULL);
}

t_job			*get_job_by_id(char *id)
{
	size_t	jobspec;
	t_job	*job;

	if (id[0] != '%')
		return (NULL);
	if (ft_strcmp(id, "%%") == 0 || ft_strcmp(id, "%+") == 0)
		return (g_shell.current_job);
	if (ft_strcmp(id, "%-") == 0)
		return (g_shell.previous_job);
	if (id[1] >= '0' && id[1] <= '9')
	{
		jobspec = (size_t)ft_atoi(id + 1);
		job = g_shell.head_job;
		while (job)
		{
			if (job->jobspec == jobspec)
				return (job);
			job = job->next;
		}
		return (NULL);
	}
	return (get_job_by_id_end(id));
}
