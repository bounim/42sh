/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_job.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 11:44:19 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/27 11:44:20 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	mark_job_as_running(t_job *job)
{
	t_proc	*proc;

	proc = job->head_proc;
	while (proc)
	{
		proc->stopped = 0;
		proc = proc->next;
	}
}

void	continue_job(t_job *job, int foreground)
{
	mark_job_as_running(job);
	if (foreground)
		put_in_foreground(job, 1);
	else
		put_in_background(job, 1);
}
