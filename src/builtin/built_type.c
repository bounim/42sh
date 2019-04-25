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
	char	*path;

	if (check_builtin(name))
	{
		printer_str(&g_shell.err, name);
		printer_str(&g_shell.err, " is a shell builtin\n");
	}
	else if ((path = find_command(name, envl)))
	{
		printer_str(&g_shell.err, name);
		printer_str(&g_shell.err, " is ");
		printer_str(&g_shell.err, path);
		printer_endl(&g_shell.err);
		free(path);
	}
	else
	{
		printer_str(&g_shell.err, "type: ");
		printer_str(&g_shell.err, name);
		printer_str(&g_shell.err, ": not found\n");
		return (1);
	}
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
	printer_flush(&g_shell.err);
	return (r);
}
