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

static void	job_notif_continue(t_job **job, t_job **last_job, t_job **next_job)
{
	while (job)
	{
		*next_job = (*job)->next;
		if (job_is_completed(*job))
		{
			format_job_info(*job, "completed");
			if (*last_job)
				(*last_job)->next = (*job)->next;
			else
				(*last_job) = g_shell.head_job;
			free_job(*job);
			*job = (*job)->next;
		}
		else if (job_is_stopped(*job) && !(*job)->notified)
		{
			format_job_info(*job, "stopped");
			(*job)->notified = 1;
			*last_job = *job;
		}
		else
			*last_job = *job;
	}
}

void		job_notif(void)
{
	t_job	*job;
	t_job	*last_job;
	t_job	*next_job;

	update_status();
	last_job = NULL;
	job = g_shell.head_job;
	job_notif_continue(&job, &last_job, &next_job);
}
