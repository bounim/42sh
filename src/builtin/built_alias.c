/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_alias.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:07:38 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/21 16:15:30 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int		check_opts_alias(char **arg, int *opts)
{
	t_opts	flag;
	int		i;

	i = 0;
	if ((i = check_opts(arg, &flag, 'p')) != -1)
	{
		if (flag.p == 1)
			*opts = 1;
		return (i);
	}
	ft_putstr_fd("alias: usage: alias [-p] [name[=value] ... ]\n", 2);
	return (-1);
}

static int		alias_var_egual(char *arg, t_alias **alias)
{
	t_alias	*tmp;
	char	*name;
	char	*value;
	int		i;

	if (!(i = ft_strichr(arg, '=')))
		return (0);
	value = ft_strsub(arg, i + 1, ft_strlen(arg) - i);
	tmp = *alias;
	while (tmp)
	{
		if (ft_strequ(tmp->name, arg))
		{
			ft_strdel(&(tmp->value));
			tmp->value = value;
			return (1);
		}
		tmp = tmp->next;
	}
	name = ft_strsub(arg, 0, i);
	tmp = new_alias(name, value);
	*alias = addlast_alias(*alias, tmp);
	ft_strdel(&name);
	ft_strdel(&value);
	return (1);
}

static int		alias_var(char *arg, t_alias **alias)
{
	t_alias	*tmp;

	tmp = *alias;
	while (tmp)
	{
		if (ft_strequ(arg, tmp->name))
		{
			ft_putstr("alias ");
			ft_putstr(tmp->name);
			ft_putchar('=');
			ft_putstr(tmp->value);
			return (0);
		}
		tmp = tmp->next;
	}
	ft_putstr_fd("alias: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": not found\n", 2);
	return (1);
}

int		built_alias(char **arg, t_alias **alias)
{
	int	i;
	int	opts;

	if ((i = check_opts_alias(arg, &opts)) == -1)
		return (1);
	if (opts == 1)
		print_alias(*alias);
	while (arg[i])
	{
		if (ft_strchr(arg[i], '='))
			alias_var_egual(arg[i], alias);
		else
			alias_var(arg[i], alias);
		i++;
	}
	return (0);
}
