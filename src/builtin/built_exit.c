/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 15:18:44 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/25 18:47:43 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void	print_exit_error_message(char *arg)
{
	printer_str(&g_shell.err, g_shell.progname);
	printer_str(&g_shell.err, ": exit: ");
	printer_str(&g_shell.err, arg);
	printer_str(&g_shell.err, ": numeric argument required\n");
	printer_flush(&g_shell.err);
}

static int	check_if_exit_arg_is_digit(char **arg)
{
	if (arg)
	{
		if (!arg[1])
			return (0);
		if (arg[1])
		{
			if (arg[1][0] == '-')
			{
				if (ft_strisdigit(arg[1] + 1) != 0)
				{
					print_exit_error_message(arg[1]);
					return (-1);
				}
			}
			else if (ft_strisdigit(arg[1]) != 0)
			{
				print_exit_error_message(arg[1]);
				return (-1);
			}
		}
	}
	return (0);
}

static int	check_exit_arg_nb(char **arg)
{
	if (arg)
	{
		if (arg[1])
		{
			if (arg[2])
			{
				write_error("exit", "too many arguments");
				return (-1);
			}
		}
	}
	return (0);
}

int			built_exit(char **arg, t_envl *envl)
{
	int		r;

	(void)envl;
	r = g_shell.exit_code;
	if (g_shell.pgid == getpid())
	{
		printer_str(&g_shell.err, "exit\n");
		printer_flush(&g_shell.err);
	}
	if (check_exit_arg_nb(arg) == -1)
		return (1);
	file_from_history(g_shell.hist.history);
	if (check_if_exit_arg_is_digit(arg) < 0)
		r = 255;
	else if (arg)
		if (arg[1])
			r = ft_atoi(arg[1]);
	clean_shell();
	exit(r);
}
