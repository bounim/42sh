/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_jobs2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 05:24:58 by emartine          #+#    #+#             */
/*   Updated: 2019/05/07 05:24:59 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

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
