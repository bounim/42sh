/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:15:04 by kberisha          #+#    #+#             */
/*   Updated: 2019/04/22 14:15:08 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"
#include "execution.h"

void			write_error(char *cmd, char *str)
{
	printer_str(&g_shell.err, g_shell.progname);
	printer_str(&g_shell.err, ": ");
	printer_str(&g_shell.err, cmd);
	printer_str(&g_shell.err, ": ");
	printer_str(&g_shell.err, str);
	printer_endl(&g_shell.err);
	printer_flush(&g_shell.err);
}

void			exec_error(char *cmd, int r)
{
	if (r < 0)
		write_error(cmd, "command not found");
	else if (r == 1)
		write_error(cmd, "cannot stat");
	else if (r == 2)
		write_error(cmd, "is a directory");
	else if (r == 3)
		write_error(cmd, "Permission denied");
}
