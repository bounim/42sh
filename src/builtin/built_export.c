/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 12:29:37 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/13 15:59:53 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	error_export(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]))
	{
		ft_putstr_fd("export: '", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valide identifier", 2);
		return (1);
	}
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		if (!ft_isalnum(arg[i]))
		{
			ft_putstr_fd("export: '", 2);
			ft_putstr_fd(arg, 2);
			ft_putendl_fd("': not a valide identifier", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	start_arg_export(char **arg, int *opts)
{
	int	i;
	
	i = 1;
	*opts = 0;
	while (arg[i])
	{
		if (ft_strequ(arg[i], "-p"))
			*opts = 1;
		else if (ft_strequ(arg[i], "--"))
			return (i + 1);
		else
			return (i);
		i++;
	}
	return (i);
}

static int	export_var_egual(char *arg, t_envl **env)
{
	t_envl	*tmp;
	char	*name;
	char	*value;
	int		i;

	if (!(i = ft_strichr(arg, '=')))
		return (0);
	value = ft_strsub(arg, i + 1, ft_strlen(arg) - i);
	tmp = *env;
	while (tmp)
	{
		if (ft_strequ(tmp->name, arg))
		{
			ft_strdel(&(tmp->value));
			tmp->value = value;
			tmp->exp = 1;
			return (1);
		}
		tmp = tmp->next;
	}
	name = ft_strsub(arg, 0, i);
	push_env(env, name, value, 1);
	ft_strdel(&name);
	ft_strdel(&value);
	return (1);
}

static int	export_var(char *arg, t_envl **env)
{
	t_envl	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strequ(tmp->name, arg))
		{
			tmp->exp = 1;
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int			built_export(char **arg, t_envl **envl)
{
	int	i;
	int	len;
	int	opts;

	len = ft_arrlen(arg);
	i = start_arg_export(arg, &opts);
	if (len == 1 || opts == 1 || arg[i] == NULL)
		print_envl(*envl, 1);
	while (arg[i])
	{
		if (!error_export(arg[i]))
		{
			if (ft_strchr(arg[i], '='))
				export_var_egual(arg[i], envl);
			else
				export_var(arg[i], envl);
		}
		i++;
	}
	return (0);
}
