/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_bg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 13:31:55 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/28 16:35:23 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	check_opts_bg(char **arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (ft_strequ(arg[i], "-"))
			return (i);
		if (ft_strequ(arg[i], "--"))
			return (i + 1);
		else if (ft_strnequ(arg[i], "-", 1))
		{
			ft_putstr_fd("sh: bg: -", 2);
			write(2, arg[i] + 1, 1);
			ft_putstr_fd(": invalid option\nfg: usage: bg [job_spec ...]\n", 2);
			return (-1);
		}
		else
			return (i);
		i++;
	}
	return (i);
}

static int	print_error_bg(int nb)
{
	ft_putstr_fd("sh: bg: ", 2);
	ft_putnbr_fd(nb, 2);
	ft_putstr_fd(": no such job\n", 2);
	return (1);
}

static int	run_bg(char **arg, t_job *job, int i)
{
	int		j;
	int		k;
	int		ret;
	t_job	*tmp;

	ret = 0;
	while (arg[i])
	{
		j = ft_atoi(arg[i]);
		k = 0;
		tmp = job;
		if (j == 0)
			ret = print_error_bg(0);
		else
		{
			while (k++ < j && tmp)
				job = job->next;
			if (tmp)
				continue_job(job, 0);
			else
				ret = 1;
		}
	}
	return (ret);
}

int			built_bg(char **arg, t_job *job)
{
	int	i;

	if ((i = check_opts_bg(arg)) == -1)
		return (1);
	return (run_bg(arg, job, i));
}
