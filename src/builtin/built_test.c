/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:31:02 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/25 15:22:12 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int			unexpected(char *cmd, char *arg, char *reason)
{
	printer_str(&g_shell.err, g_shell.progname);
	printer_str(&g_shell.err, ": ");
	printer_str(&g_shell.err, cmd);
	printer_str(&g_shell.err, ": ");
	printer_str(&g_shell.err, arg);
	printer_str(&g_shell.err, ": ");
	printer_str(&g_shell.err, reason);
	printer_str(&g_shell.err, " expected\n");
	printer_flush(&g_shell.err);
	return (2);
}

static int	built_test_end(int argc, char **av, char *cmd, int r)
{
	if (argc == 3)
	{
		if (av[1][0] == '-' || av[1][2] == '\0')
			return (unary_test(cmd, av[1], av[2]) ^ r);
		return (unexpected(cmd, av[1], "unary operator"));
	}
	if (argc == 4)
	{
		return (binary_test(cmd, av[1], av[2], av[3]) ^ r);
	}
	write_error("test", "too many arguments");
	return (2);
}

int			built_test(char **av, t_envl *envl)
{
	char	*cmd;
	int		r;
	int		argc;

	(void)envl;
	argc = ft_arrlen(av);
	cmd = av[0];
	r = 1;
	while (1)
	{
		if (argc <= 1)
			return (0 ^ r);
		if (argc == 2)
			return ((av[1][0] != '\0') ^ r);
		if (av[1][0] == '!' && av[1][1] == '\0')
		{
			r ^= 1;
			argc--;
			av++;
			continue ;
		}
		return (built_test_end(argc, av, cmd, r));
	}
}
