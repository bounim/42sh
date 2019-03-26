/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:28:52 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/26 11:45:34 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

/*
static	t_opt	*init_opt(t_opt *flag)
{
	flag->c = 0;
	flag->d = 0;
	flag->a = 0;
	flag->n = 0;
	flag->r = 0;
	flag->w = 0;
	flag->p = 0;
	flag->s = 0;
	flag->nb = 0;
	return (flag);
}

static int		add_flag(t_opt *flag, char c)
{
	if (c == 'c')
		flag->c = 1;
	else if (c == 'd')
		flag->d = 1;
	else if (c == 'a')
		flag->a = 1;
	else if (c == 'n')
		flag->n = 1;
	else if (c == 'r')
		flag->r = 1;
	else if (c == 'w')
		flag->w = 1;
	else if (c == 'p')
		flag->p = 1;
	else if (c == 's')
		flag->s = 1;
	else
		return (1);
	flag->nb = 1;
	return (0);
}

static int	check_opt(t_opt *flag, char **arg)
{
	int		i;
	int		j;

	if (!(flag = (t_opt *)malloc(sizeof(*flag))))
		return (1);
	flag = init_opt(flag);
	i = 1;
	while (arg[i])
	{
		if (ft_strequ(arg[i], "--"))
			return (i + 1);
		else if (arg[i][0] == '-')
		{
			j = 1;
			while (arg[i][j])
			{
				if (add_flag(flag, arg[i][j]))
				{
					ft_putstr_fd("sh: history: -", 2);
					write(2, arg[i] + j, 1);
					ft_putstr_fd(": invalid option\nhistory: usage: history [-c] \
						[-d offset] [n] or history -awrn [filename] or \
						history -ps arg [arg...]\n", 2);
					return (-1);
				}
				j++;
			}
		}
		else
			return (i);
	}
	return (i);
}
*/
int			built_history(char **arg, t_history **hist)
{
//	int		i;
//	t_opt	flag;
	int		len;

	if ((len = ft_arrlen(arg)) >= 1)
	{
			print_historyl(*hist);
			return (0);
	}/*
	if ((i = check_opt(&flag, arg) == -1))
		return (1);
	if (flag.nb == 0)
	{
		if (ft_strisdigit(arg[1]))
		{
			ft_putstr_fd("sh: history: ", 2);
			ft_putstr_fd(arg[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (1);
		}
		else if (len > 2)
		{
			ft_putstr_fd("sh: history: too many arguments", 2);
			return (1);
		}
		print_historyl(*hist);
	}*/
	return (1);
}
