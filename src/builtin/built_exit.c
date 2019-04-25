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
	ft_putstr("sh: exit: ");
	ft_putstr(arg);
	ft_putstr(": numeric argument required");
}

static void	check_if_exit_arg_is_digit(char **arg)
{
	if (arg)
	{
		if (!arg[1])
			return ;
		if (arg[1])
		{
			if (arg[1][0] == '-')
			{
				if (ft_strisdigit(arg[1] + 1) != 0)
					print_exit_error_message(arg[1]);
			}
			else if (ft_strisdigit(arg[1]) != 0)
				print_exit_error_message(arg[1]);
		}
	}
}

static int	check_exit_arg_nb(char **arg)
{
	if (arg)
	{
		if (arg[1])
		{
			if (arg[2])
			{
				ft_putstr("sh: exit: too many arguments\n");
				return (-1);
			}
		}
	}
	return (0);
}

int			built_exit(char **arg, t_envl *envl)
{
	(void)envl;
	if (check_exit_arg_nb(arg) == -1)
		return (-1);
	file_from_history(g_shell.hist.history);
	clean_shell();
	ft_putstr("exit\n");
	check_if_exit_arg_is_digit(arg);
	if (arg)
		if (arg[1])
			exit(ft_atoi(arg[1]));
	exit(0);
}
