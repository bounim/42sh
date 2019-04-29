/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_alias.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:07:38 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/25 15:33:08 by khsadira         ###   ########.fr       */
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

static int		alias_var_egual(char *arg, t_alias **alias, int i)
{
	t_alias	*tmp;
	char	*name;
	char	*value;

	if (i == -1)
		return (1);
	name = ft_strsub(arg, 0, i);
	value = ft_strsub(arg, i + 1, ft_strlen(arg) - i);
	tmp = *alias;
	while (tmp)
	{
		if (ft_strequ(tmp->name, name))
		{
			ft_strdel(&name);
			ft_strdel(&(tmp->value));
			tmp->value = value;
			return (0);
		}
		tmp = tmp->next;
	}
	tmp = new_alias(name, value);
	*alias = addlast_alias(*alias, tmp);
	ft_strdel(&name);
	ft_strdel(&value);
	return (0);
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
			ft_putendl(tmp->value);
			return (0);
		}
		tmp = tmp->next;
	}
	ft_putstr_fd("alias: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": not found\n", 2);
	return (1);
}

int				built_alias(char **arg, t_envl *envl)
{
	int	i;
	int	opts;
	int	ret;

	(void)envl;
	ret = 0;
	opts = 0;
	if ((i = check_opts_alias(arg, &opts)) == -1)
		return (1);
	if (opts == 1)
		ret += print_alias(g_shell.alias);
	else if (!arg[i])
		ret += print_alias(g_shell.alias);
	while (arg[i])
	{
		if (ft_strchr(arg[i], '='))
			ret += alias_var_egual(arg[i], &g_shell.alias,
					ft_strichr(arg[i], '='));
		else
			ret += alias_var(arg[i], &g_shell.alias);
		i++;
	}
	if (ret > 0)
		return (1);
	return (0);
}
