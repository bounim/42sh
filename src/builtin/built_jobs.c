/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_jobs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 21:39:18 by emartine          #+#    #+#             */
/*   Updated: 2019/05/03 21:39:19 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

#define JOBS_ARG_L (1 << 1)
#define JOBS_ARG_P (1 << 2)

static void	process_list(t_job *job)
{
	printer_int(&g_shell.out, (int)job->pgid);
	printer_endl(&g_shell.out);
}

static void	print_state(t_printer *pr, t_job *job, int exit_code)
{
	if (job->stopped)
	{
		printer_str(pr, "Stopped (");
		print_signal(pr, job->sig);
		printer_char(pr, ')');
	}
	else if (job->running > 0)
		printer_str(pr, "Running");
	else if (job->sig)
	{
		printer_str(pr, "Terminated (");
		print_signal(pr, job->sig);
		printer_char(pr, ')');
	}
	else
	{
		printer_str(pr, "Done");
		if (exit_code)
		{
			printer_char(pr, '(');
			printer_int(pr, exit_code);
			printer_char(pr, ')');
		}
	}
}

void		detailed_list(t_printer *pr, t_job *job, int show_pgid,
		int exit_code)
{
	printer_char(pr, '[');
	printer_ulong(pr, job->jobspec);
	printer_bin(pr, (uint8_t *)"] ", 2);
	if (job == g_shell.current_job)
		printer_char(pr, '+');
	else if (job == g_shell.previous_job)
		printer_char(pr, '-');
	else
		printer_char(pr, ' ');
	printer_char(pr, ' ');
	if (show_pgid)
	{
		printer_int(pr, (int)job->pgid);
		printer_char(pr, ' ');
	}
	print_state(pr, job, exit_code);
	printer_char(pr, ' ');
	printer_str(pr, job->cmd);
	printer_endl(pr);
}

static void	list_one(int opt, t_job *job)
{
	if (opt == JOBS_ARG_L)
		detailed_list(&g_shell.out, job, 1, 0);
	else if (opt == JOBS_ARG_P)
		process_list(job);
	else
		detailed_list(&g_shell.out, job, 0, 0);
}

static void	list_all(int opt)
{
	t_job	*job;

	job = g_shell.head_job;
	while (job)
	{
		if (job->pgid)
			list_one(opt, job);
		job = job->next;
	}
}

int			built_jobs(char **argv, t_envl *envl)
{
	int		opt;
	size_t	i;
	t_job	*job;

	(void)envl;
	check_background(1);
	opt = 0;
	i = 1;
	if (argv[1] && argv[1][0] == '-')
	{
		if (argv[1][1] == 'l')
			opt = JOBS_ARG_L;
		else if (argv[1][1] == 'p')
			opt = JOBS_ARG_P;
		i++;
	}
	if (!argv[i])
		list_all(opt);
	else
	{
		while (argv[i])
		{
			if ((job = get_job_by_id(argv[i])))
				list_one(opt, job);
			i++;
		}
	}
	printer_flush(&g_shell.out);
	return (0);
}
