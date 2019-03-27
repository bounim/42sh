/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 15:20:07 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/27 15:27:44 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

t_job	*init_job(t_job *job)
{
	if (!(job = (t_job *)malloc(sizeof(t_job))))
		return (NULL);
	job->status = 0;
	job->cmd = NULL;
	job->head_proc = NULL;
	job->pgid = 0;
	job->notified = 0;
	job->tmodes = NULL;
	job->next = NULL;
}

t_proc	*init_proc(t_proc *proc)
{
	if (!(proc = (t_proc *)malloc(sizeof(t_proc))))
		return (NULL);
	proc->status = 0;
	proc->arg = NULL;
	proc->env = NULL;
	proc->pid = 0;
	proc->finish = 0;
	proc->stop = 0;
	proc->status = 0;
	proc->next = NULL;
}
