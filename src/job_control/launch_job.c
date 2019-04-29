/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 11:44:16 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/24 13:51:47 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void		close_pipe_error(t_job *job, t_proc *err)
{
	t_proc	*cur;

	cur = job->head_proc;
	while (cur && cur != err)
	{
		close(cur->tunnel[0]);
		close(cur->tunnel[1]);
		cur = cur->next;
	}
	fatal_exit(SH_ENOPIPE);
}

void			launch_job(t_job *job)
{
	t_proc	*cur;
	int		std_file[2];

	std_file[0] = STDIN_FILENO;
	cur = job->head_proc;
	if (cur && !cur->next)
		launch_proc(cur);
	else if (cur)
	{
		while (cur->next)
		{
			if (pipe(cur->tunnel) < 0)
			{
				close_pipe_error(job, cur);
				return ;
			}
			cur = cur->next;
		}
		cur = job->head_proc;
		while (cur)
		{
			launch_proc(cur);
			cur = cur->next;
		}
	}
}
