/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_fg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 21:39:24 by emartine          #+#    #+#             */
/*   Updated: 2019/05/03 21:39:25 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

t_job	*built_bg_fg_job(char **arg)
{
	t_job	*job;

	check_background(1);
	if (g_shell.background || g_shell.pgid != getpid())
	{
		write_error(arg[0], "no job control");
		return (NULL);
	}
	if (arg[1])
	{
		if (!(job = get_job_by_id(arg[1])))
		{
			write_error(arg[0], "no such job");
			return (NULL);
		}
		return (job);
	}
	if (!g_shell.current_job)
	{
		write_error(arg[0], "no current job");
		return (NULL);
	}
	return (g_shell.current_job);
}

int		built_fg(char **arg, t_envl *envl)
{
	t_job	*job;

	(void)envl;
	if (!(job = built_bg_fg_job(arg)))
		return (1);
	printer_str(&g_shell.out, job->cmd);
	printer_endl(&g_shell.out);
	printer_flush(&g_shell.out);
	wait_job(job, 1);
	if (job->running == 0)
		remove_job(job);
	return (g_shell.exit_code);
}
