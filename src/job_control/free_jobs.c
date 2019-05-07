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

void		free_proc(t_proc *proc)
{
	if (!proc)
		return ;
	if (!proc->cmd)
		ft_arrdel(proc->arg);
	else
		free(proc->arg);
	if (proc->envl)
		free_envl(proc->envl);
	if (proc->env)
		ft_arrdel(proc->env);
	free(proc);
}

void		free_job(t_job *job)
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

void		free_exec(void)
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

static void	unset_current_job(t_job *del)
{
	t_job	*cur;

	if (del == g_shell.previous_job)
		g_shell.previous_job = NULL;
	if (del == g_shell.current_job)
		g_shell.current_job = NULL;
	if (!g_shell.head_job)
		return ;
	if (!g_shell.current_job)
	{
		if (g_shell.previous_job)
		{
			g_shell.current_job = g_shell.previous_job;
			g_shell.previous_job = NULL;
		}
		else
		{
			cur = g_shell.head_job;
			while (cur->next && cur->next->next)
				cur = cur->next;
			if (cur->next)
			{
				g_shell.previous_job = cur;
				g_shell.current_job = cur->next;
			}
			else
				g_shell.current_job = cur;
			return ;
		}
	}
	if (!g_shell.previous_job)
	{
		cur = g_shell.current_job->next ? g_shell.current_job->next
			: g_shell.head_job;
		while (cur->next && cur->next != g_shell.current_job)
			cur = cur->next;
		g_shell.previous_job = cur;
	}
}

void		remove_job(t_job *job)
{
	t_job	*prev;
	t_job	*cur;

	if (job && g_shell.head_job)
	{
		if (g_shell.head_job == job)
			g_shell.head_job = g_shell.head_job->next;
		else
		{
			prev = g_shell.head_job;
			cur = g_shell.head_job->next;
			while (cur)
			{
				if (cur == job)
				{
					prev->next = cur->next;
					break ;
				}
				prev = cur;
				cur = cur->next;
			}
		}
	}
	unset_current_job(job);
	free_job(job);
}
