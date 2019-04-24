/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:31:02 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/22 16:41:38 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int			unexpected(char *cmd, char *arg, char *reason)
{
	write(1, "21sh: ", 6);
	ft_putstr(cmd);
	ft_putstr(": ");
	ft_putstr(arg);
	ft_putstr(": ");
	ft_putstr(reason);
	write(1, "\n", 1);
	return (2);
}

int			get_ac(char **av)
{
	int ret;

	ret = 0;
	while (av[ret])
		ret++;
	return (ret);
}

int			built_test_end(int argc, char **av, char *cmd, int r)
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
	write(1, "21sh: ", 6);
	ft_putstr(cmd);
	write(1, ": too many arguments\n", 21);
	return (2);
}

int			built_test(char **av, t_envl *envl)
{
	char	*cmd;
	int		r;
	int		argc;

	(void)envl;
	argc = get_ac(av);
	cmd = av[0];
	r = 1;
	while (1)
	{
		if (argc <= 1)
			return (1 ^ r);
		if (argc == 2)
			return ((av[1][0] == '\0') ^ r);
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
