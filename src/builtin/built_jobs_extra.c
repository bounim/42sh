/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_jobs_extra.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:01:03 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/28 17:01:02 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static t_opt_jobs	*init_opt_jobs(t_opt_jobs *opts)
{
	if (!(opts = (t_opt_jobs *)malloc(sizeof(t_opt_jobs))))
		return (NULL);
	opts->l = 0;
	opts->n = 0;
	opts->p = 0;
	opts->r = 0;
	opts->s = 0;
	opts->x = 0;
	return (opts);
}

static void			*print_error_jobs(char *arg)
{
	ft_putstr_fd("sh: alias: -", 2);
	write(2, arg, 1);
	ft_putstr_fd(": invalid option\nalias: usage: \
		alias[-lnprs] [jobspec] or jobs -x command [args]\n", 2);
	return (NULL);
}

static t_opt_jobs	*empty_opts(char *arg, t_opt_jobs *opts)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] == 'x')
			opts->x = 1;
		else if (arg[i] == 'l')
			opts->l = 1;
		else if (arg[i] == 'n')
			opts->n = 1;
		else if (arg[i] == 'p')
			opts->p = 1;
		else if (arg[i] == 'r')
			opts->n = 1;
		else if (arg[i] == 's')
			opts->s = 1;
		else
			return (print_error_jobs(arg + i));
		i++;
	}
	return (opts);
}

int					check_opts_jobs(char **arg, t_opt_jobs *jobs)
{
	int	i;

	i = 1;
	if (!(jobs = init_opt_jobs(jobs)))
		return (-1);
	while (arg[i])
	{
		if (ft_strequ(arg[i], "-"))
			return (i);
		else if (ft_strequ(arg[i], "--"))
			return (i + 1);
		else if (ft_strnequ(arg[i], "-", 1))
		{
			if (!(jobs = empty_opts(arg[i], jobs)))
				return (-1);
			else
				return (i);
		}
		i++;
	}
	return (i);
}
