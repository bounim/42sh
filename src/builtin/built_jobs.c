/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_jobs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 16:41:35 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/11 12:10:13 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void	print_jobs_continue(t_job *jobs, t_opt_jobs opts, int i)
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
	if (opts.l == 1)
	{
		ft_putnbr(jobs->pgid);
		ft_putstr(" ");
	}
	if (opts.l == 1)
		ft_putstr("Suspended: 18\t");
	else
		ft_putstr("Stopped(SIGTSTP)\t");
	ft_putendl(jobs->cmd);
}

static int	print_jobs(t_job *jobs, t_opt_jobs opts)
{
	int	i;

	i = 1;
	while (jobs->next)
	{
		if (opts.p)
		{
			ft_putnbr(jobs->pgid);
			ft_putstr("\n");
		}
		else
			print_jobs_continue(jobs, opts, i);
		jobs = jobs->next;
	}
	return (0);
}

int			built_jobs(char **arg, t_envl *envl)
{
	t_opt_jobs	opts;
	int			i;
	char		**ret;
	t_job		*job;

	(void)envl;
	if (!(job = g_shell.head_job))
		return (-1);
	ret = NULL;
	if ((i = check_opts_jobs(arg, &opts)) == -1)
		return (1);
	return (print_jobs(job, opts));
}
