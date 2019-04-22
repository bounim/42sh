/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 11:44:16 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/10 18:42:20 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

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
				cur->tunnel[0] = -1;
				cur->tunnel[1] = -1;
				//free_job(job);
				return ; // TODO
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
