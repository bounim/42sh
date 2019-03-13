/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_setenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:30:03 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/13 12:20:15 by khsadira         ###   ########.fr       */
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
			ft_strdel(&(tmp->value));
			tmp->value = ft_strdup("");
			return (0);
		}
		tmp = tmp->next;
	}
	push_env(head, arg, "", 1);
	return (0);
}

int			built_setenv(char **arg, t_envl **envl)
{
	t_envl	*tmp;
	int		len;

	tmp = *envl;
	if ((len = ft_arrlen(arg)) == 1)
	{
		print_envl(*envl);
		return (0);
	}
	else if (built_setenv_check_error(arg))
		return (1);
	else if (len == 2)
		return (setenv_nullarg(arg[1], envl));
	while (tmp)
	{
		if (ft_strequ(tmp->name, arg[1]) && tmp->exp == 0)
		{
			ft_strdel(&(tmp->value));
			tmp->value = ft_strdup(arg[2]);
			tmp->exp = 1;
			return (0);
		}
		tmp = tmp->next;
	}
	push_env(envl, arg[1], arg[2], 1);
	return (0);
}
