/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 10:46:11 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/25 15:28:30 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	print_type(char *name, t_envl *envl)
{
	char	path[PATH_MAX + 1];

	if (check_builtin(name))
	{
		printer_str(&g_shell.out, name);
		printer_str(&g_shell.out, " is a shell builtin\n");
	}
	else if (find_command(path, name, envl) == 0)
	{
		printer_str(&g_shell.out, name);
		printer_str(&g_shell.out, " is ");
		printer_str(&g_shell.out, path);
		printer_endl(&g_shell.out);
	}
	else
	{
		printer_str(&g_shell.err, "type: ");
		printer_str(&g_shell.err, name);
		printer_str(&g_shell.err, ": not found\n");
		printer_flush(&g_shell.err);
		return (1);
	}
	printer_flush(&g_shell.out);
	return (0);
}

int			built_type(char **arg, t_envl *envl)
{
	size_t	i;
	int		r;

	if (!arg[1])
		return (1);
	r = 0;
	i = 1;
	while (arg[i])
	{
		r |= print_type(arg[i], envl);
		i++;
	}
	return (r);
}
