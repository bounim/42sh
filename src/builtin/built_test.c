/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:31:02 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/19 17:31:03 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int			unexpected(char *cmd, char *arg, char *reason)
{
	printf("21sh: %s: %s: %s expected\n", cmd, arg, reason);
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
		printf("21sh: %s: too many arguments\n", cmd);
		return (2);
	}
}