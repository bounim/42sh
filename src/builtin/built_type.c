/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 10:46:11 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/15 13:06:46 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"
/*
static typedef struct	s_opts;
{
	int		a;
	int		f;
	int		p;
	int		t;
	int		P;
}						t_opts;

static void				init_opts(t_opts *opts)
{
	opts->a = 0;
	opts->f = 0;
	opts->p = 0;
	opts->t = 0;
	opts->P = 0;
}

static int				start_arg_type(char **arg, t_opts *opts)
{
	int		i;

	i = 1;
	init_opts(&(*opts));
	while (arg[i])
	{
		if (ft_strequ(arg[i], "-a"))
			opts->a = 1; 
		else if (ft_strequ(arg[i], "-f"))
			opts->f = 1; 
		else if (ft_strequ(arg[i], "-p"))
			opts->p = 1; 
		else if (ft_strequ(arg[i], "-t"))
			opts->t = 1; 
		else if (ft_strequ(arg[i], "-P"))
			opts->P = 1; 
		else if (ft_stequ(arg[i], "--"))
			return (i + 1);
		else if (ft_check_opts(arg[i]))
		{
			ft_putstr_fd("type: ", 2);
			ft_putstr_fd(, 2);
			ft_putstr_fd(, 2);
		}
		else
			return (i);
		i++;
	}
			return (i);
}

int						built_type(char **arg, t_envl **envl)
{
	int		i;
	t_opts	opts;

	if ((i = opts_type(arg, &opts)) == -1)
	{
		ft_putstr_fd("type: usage: type [-afptP] name [name ...]\n" ,2);
		return (1);
	}
}*/
int						built_type(char **arg, t_envl **envl);
