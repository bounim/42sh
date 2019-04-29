/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 15:20:07 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/24 13:51:33 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

t_job	*init_job(void)
{
	t_job	*job;

	if (!(job = (t_job *)malloc(sizeof(t_job))))
		return (NULL);
	ft_memset(job, 0, sizeof(*job));
	return (job);
}

t_proc	*init_proc(void)
{
	t_proc	*proc;

	if (!(proc = (t_proc *)malloc(sizeof(t_proc))))
		return (NULL);
	ft_memset(proc, 0, sizeof(*proc));
	return (proc);
}
