/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 16:17:22 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/09 13:48:23 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void		format_job_info(t_job *job, const char *status)
{
	ft_putnbr_fd((int)job->pgid, 2);
	ft_putstr_fd(" ", 2);
	ft_putstr_fd(status, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(job->cmd, 2);
	write(2, "\n", 1);
}

static void	job_notif_continue(t_job *job, t_job *last_job, t_job *next_job)
{
	while (job)
	{
		next_job = job->next;
		printf("start notif\n");
		if (job_is_finish(job))
		{
			format_job_info(job, "completed");
			if (last_job)
				last_job->next = next_job;
			else
				g_shell.head_job = next_job;
			free_job(job);
			printf("end of completed");
		}
		else if (job_is_stop(job) && !job->notified)
		{
			format_job_info(job, "stopped");
			job->notified = 1;
			last_job = job;
		}
		else
			last_job = job;
		job = job->next;
	}
}

void		job_notif(void)
{
	t_job	*job;
	t_job	*last_job;
	t_job	*next_job;

	update_status();
	last_job = NULL;
	next_job = NULL;
	job = g_shell.head_job;
	job_notif_continue(job, last_job, next_job);
}
