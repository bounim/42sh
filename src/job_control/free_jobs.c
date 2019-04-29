/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_jobs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 17:15:08 by emartine          #+#    #+#             */
/*   Updated: 2019/04/29 17:15:10 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	free_proc(t_proc *proc)
{
	if (!proc)
		return ;
	free(proc->arg);
	if (proc->envl)
		free_envl(proc->envl);
	free(proc);
}

void	free_job(t_job *job)
{
	t_proc	*proc;
	t_proc	*next;

	if (!job)
		return ;
	proc = job->head_proc;
	while (proc)
	{
		next = proc->next;
		free_proc(proc);
		proc = next;
	}
	free(job->cmd);
	free(job);
}

void	free_exec(void)
{
	t_job	*job;
	t_job	*next;

	job = g_shell.head_job;
	while (job)
	{
		next = job->next;
		free_job(job);
		job = next;
	}
	g_shell.head_job = NULL;
}
