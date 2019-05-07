/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_jobs2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 05:32:20 by emartine          #+#    #+#             */
/*   Updated: 2019/05/07 05:32:22 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	set_current_job(void)
{
	t_job	*cur;

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
			return (-1);
		}
	}
	return (0);
}

static void	set_previous_job(void)
{
	t_job	*cur;

	if (!g_shell.previous_job)
	{
		cur = g_shell.current_job->next ? g_shell.current_job->next
			: g_shell.head_job;
		while (cur->next && cur->next != g_shell.current_job)
			cur = cur->next;
		g_shell.previous_job = cur;
	}
}

static void	unset_current_job(t_job *del)
{
	if (del == g_shell.previous_job)
		g_shell.previous_job = NULL;
	if (del == g_shell.current_job)
		g_shell.current_job = NULL;
	if (!g_shell.head_job)
		return ;
	if (set_current_job() < 0)
		return ;
	set_previous_job();
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
