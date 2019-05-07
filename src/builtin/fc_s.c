/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:31:18 by aguillot          #+#    #+#             */
/*   Updated: 2019/05/02 15:03:49 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int	fast_exec(char *buf[3], char ed_path[PATH_MAX + 1], t_envl *envl)
{
	g_shell.fast_exec_job = NULL;
	create_proc_argv(&g_shell.fast_exec_job, ed_path, buf, envl);
	launch_job(&g_shell.fast_exec_job);
	if (g_shell.fast_exec_job)
	{
		g_shell.fast_exec_job = NULL;
		return (1);
	}
	g_shell.fast_exec_job = NULL;
	return (g_shell.exit_code > 0);
}

int	fc_s(uint8_t **buff, int len)
{
	if (len <= 0)
		return (1);
	if (*buff[len - 1] != '\n')
		*(buff) = (uint8_t*)ft_strfjoin((char*)*buff, "\n", 0);
	ft_putstr((char*)buff);
	return (0);
}
