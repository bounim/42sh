/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 12:29:37 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/24 14:18:26 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	start_arg_export(char **arg, int *opts)
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
	ft_putstr_fd("export: usage: export [name [=value ...] or export -p\n", 2);
	return (-1);
}

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
			return (0);
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

static int	export_var_equal(char *arg, t_envl **env)
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

int			built_export(char **arg, t_envl *envl)
{
	int		i;
	int		len;
	int		opts;
	t_envl	*tmp;

	opts = 0;
	if ((i = start_arg_export(arg, &opts) - 1) == -2)
		return (1);
	if ((len = ft_arrlen(arg)) == 1 || opts == 1 || arg[i] == NULL)
		print_envl(g_shell.envl, 1);
	tmp = dup_envl(envl);
	free_envl(g_shell.envl);
	g_shell.envl = tmp;
	while (arg[++i])
	{
		if (!error_export(arg[i]))
		{
			if (ft_strchr(arg[i], '='))
				export_var_equal(arg[i], &g_shell.envl);
			else
				export_var(arg[i], &g_shell.envl);
		}
	}
	return (0);
}
