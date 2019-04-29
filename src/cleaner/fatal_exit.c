/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatal_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 16:48:23 by schakor           #+#    #+#             */
/*   Updated: 2019/04/22 22:57:01 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void		fatal_exit(int code)
{
	if (g_shell.is_exiting)
		return ;
	g_shell.is_exiting = 1;
	clean_shell();
	printer_str(&g_shell.err, g_shell.progname);
	printer_str(&g_shell.err, ": fatal: ");
	if (code == SH_ENOMEM)
		printer_str(&g_shell.err, "Cannot allocate memory.\n");
	else if (code == SH_EINVAL)
		printer_str(&g_shell.err, "Invalid argument.\n");
	else if (code == SH_ENOTTY)
		printer_str(&g_shell.err, "Inappropriate ioctl device.\n");
	else if (code == 7)
		printer_str(&g_shell.err, "Exec format error\n");
	else if (code == SH_ENOPIPE)
		printer_str(&g_shell.err, "Too many open files\n");
	else
		printer_str(&g_shell.err, "exit\n");
	printer_flush(&g_shell.err);
	exit(127);
}
