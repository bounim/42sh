/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_fg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 11:53:53 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/27 16:42:21 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	check_opts_fg(char **arg)
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
			ft_putstr_fd("sh: fg: -", 2);
			write(2, arg[i] + 1, 1);
			ft_putstr_fd(": invalid option\nfg: usage: fg [job_spec]\n", 2);
			return (-1);
		}
		else
			return (i);
		i++;
	}
	return (i);
}

static int	print_error_fg(int nb)
{
	ft_putstr_fd("sh: fg: ", 2);
	ft_putnbr_fd(nb, 2);
	ft_putstr_fd(": no such job\n", 2);
	return (1);
}

int			built_fg(char **arg, t_job *job)
{
	int		i;
	int		j;

	if ((i = check_opts_fg(arg)) == -1)
		return (1);
	i = ft_atoi(arg[i]);	
	if (i == 0)
		return (print_error_fg(0));
	j = 0;
	while (j < i && job)
	{
		job = job->next;
		j++;
	}
	if (job)
		continue_job(job, 1);
	else
		return (print_error_fg(i));
	return (0);
}
