/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_background.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 19:12:01 by emartine          #+#    #+#             */
/*   Updated: 2019/05/06 19:12:03 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	check_background(int silent)
{
	int		status;
	pid_t	wpid;
	t_proc	*proc;

	status = 0;
	while ((wpid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG)) > 0)
	{
		if ((proc = update_job_status(NULL, wpid, status, silent)))
		{
			if (proc->job->running == 0)
				remove_job(proc->job);
		}
		status = 0;
	}
}
