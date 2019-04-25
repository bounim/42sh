/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_setenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:30:03 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/25 15:20:29 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	setenv_nullarg(char *arg, t_envl **head)
{
	t_envl	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (ft_strequ(tmp->name, arg))
		{
			if (tmp->exp == 0 || tmp->read_only == 1)
				return (1);
			ft_strdel(&(tmp->value));
			tmp->value = ft_strdup("");
			tmp->exp = 1;
			tmp->read_only = 0;
			return (1);
		}
		tmp = tmp->next;
	}
	push_env(head, arg, "", 1);
	return (0);
}

static int	replace_setenv(char **arg, t_envl **envl)
{
	if ((*envl)->exp == 0 || (*envl)->read_only == 1)
		return (1);
	ft_strdel(&((*envl)->value));
	(*envl)->value = ft_strdup(arg[2]);
	(*envl)->read_only = 0;
	(*envl)->exp = 1;
	return (0);
}

static int	start_setenv(char **arg, t_envl **envl)
{
	t_envl	*tmp;
	int		len;

	tmp = *envl;
	if ((len = ft_arrlen(arg)) == 1)
	{
		print_envl(*envl, 0);
		return (0);
	}
	else if (built_setenv_check_error(arg))
		return (1);
	else if (len == 2)
		return (setenv_nullarg(arg[1], envl));
	while (tmp)
	{
		if (ft_strequ(tmp->name, arg[1]))
			return (replace_setenv(arg, &tmp));
		tmp = tmp->next;
	}
	push_env(envl, arg[1], arg[2], 1);
	return (0);
}

int			built_setenv(char **arg, t_envl *envl)
{
	t_envl	*tmp;

	tmp = dup_envl(envl);
	free_envl(g_shell.envl);
	g_shell.envl = tmp;
	return (start_setenv(arg, &g_shell.envl));
}
