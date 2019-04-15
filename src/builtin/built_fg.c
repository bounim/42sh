/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_fg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 11:53:53 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/15 14:47:35 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int		check_opts_fg(char **arg)
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

static int		print_error_fg(int nb)
{
	ft_putstr_fd("sh: fg: ", 2);
	ft_putnbr_fd(nb, 2);
	ft_putstr_fd(": no such job\n", 2);
	return (1);
}

static t_job	*return_job_value(t_job *job)
{
	if (!g_shell.head_job->next)
	{
		ft_putstr_fd("sh: fg: no current job\n", 2);
		return (NULL);
	}
	if (!(job = g_shell.head_job))
		return (NULL);
	return (job);
}

int				built_fg(char **arg, t_envl *envl)
{
	int		i;
	int		j;
	t_job	*job;

	(void)envl;
	if (!(job = return_job_value(NULL)))
		return (1);
	if ((i = check_opts_fg(arg)) == -1)
		return (1);
	j = 0;
	if (!arg[i])
		i = 1;
	else if ((i = ft_atoi(arg[i])))
		return (print_error_fg(0));
	j = 1;
	while (j < i && job->next)
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
