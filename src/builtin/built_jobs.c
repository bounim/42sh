/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_jobs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 16:41:35 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/28 16:26:24 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	jobs_exec(char **ret)
{
	//call de la fonction d'execution;
	ret++;
	return (0);
}

static int	print_jobs(t_job *jobs, t_opt_jobs opts)
{
	int	i;

	i = 1;
	while (jobs)
	{
		if (opts.p == 0 || (opts.n == 1 && opts.l == 1))
		{
			write(1, "[", 1);
			ft_putnbr(i);
			write(1, "]", 1);
			if (jobs->next && jobs->next->next == NULL)
				ft_putstr(" - ");
			else if (!jobs->next)
				ft_putstr(" + ");
			else
				ft_putstr("   ");
		}
		if (opts.l == 1)
			ft_putstr("Suspended: 18\t\t");
		else if (opts.p == 0)
			ft_putstr("Stopped(SIGTSTP)\t\t");
		ft_putstr(jobs->cmd);
		jobs = jobs->next;
	}
	return (0);
}

int			built_jobs(char **arg, t_job *jobs)
{
	t_opt_jobs	opts;
	int			i;
	char		**ret;

	ret = NULL;
	if ((i = check_opts_jobs(arg, &opts)) == -1)
		return (1);
	if (opts.x)
		return (jobs_exec(arg + i));
	else
		return (print_jobs(jobs, opts));
}
