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

static void		write_error(char *cmd, char *str)
{
	printer_str(&g_shell.err, "21sh: ");
	printer_str(&g_shell.err, cmd);
	printer_str(&g_shell.err, ": ");
	printer_str(&g_shell.err, str);
	printer_endl(&g_shell.err);
	printer_flush(&g_shell.err);
}

int				exec_error(char *cmd, char *path)
{
	struct stat	buf;

	if (!path)
		write_error(cmd, "command not found");
	else if (stat(path, &buf) < 0)
		write_error(path, "cannot stat");
	else if ((buf.st_mode & S_IFMT) == S_IFDIR)
		write_error(path, "is a directory");
	else if (access(path, X_OK) < 0)
		write_error(path, "Permission denied");
	else
		return (0);
	return (-1);
}
