/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_bg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 21:39:27 by emartine          #+#    #+#             */
/*   Updated: 2019/05/03 21:39:28 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int					built_bg(char **arg, t_envl *envl)
{
	t_job	*job;

	(void)envl;
	if (!(job = built_bg_fg_job(arg)))
		return (1);
	printer_char(&g_shell.out, '[');
	printer_ulong(&g_shell.out, job->jobspec);
	printer_bin(&g_shell.out, (uint8_t *)"] ", 2);
	printer_str(&g_shell.out, job->cmd);
	printer_endl(&g_shell.out);
	printer_flush(&g_shell.out);
	job->stopped = 0;
	job->background = 1;
	kill(-job->pgid, SIGCONT);
	return (0);
}
