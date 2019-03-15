/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unalias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:08:25 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/15 15:52:20 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	start_arg_unalias(char **arg, int *opts)
{
	t_opts	flag;
	int		i;

	i = 0;
	if ((i = check_opts(arg, &flag, 'a')) != -1)
	{
		if (flag.a == 1)
			*opts = 1;
		return (i);
	}
	ft_putstr_fd("unalias: usage: unalias [-a] name [name ...]\n", 2);
	return (-1);
}

int		unset_alias(char *arg, t_alias **alias)
{
	t_alias	*tmp;
	t_alias	*lst;
	
	lst = *alias;
	if (ft_strequ(arg, lst->name))
	{
		*alias = lst->next;
		lst->next = NULL;
		free_alias(lst);
		return (0);
	}
	tmp = lst;
	lst = lst->next;
	while (lst)
	{
		if (ft_strequ(lst->name, arg))
		{
			tmp->next = lst->next;
			lst->next = NULL;
			free_alias(lst);
			return (0);
			//*alias = head; ???
		}
		tmp = lst;
		lst = lst->next;
	}
	ft_putstr_fd("unalias: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": not found\n", 2);
	return (1);
}

int		built_unalias(char **arg, t_alias **alias)
{
	int	opts;
	int	i;

	if ((i = start_arg_unalias(arg, &opts)) == -1)
		return (0);
	if (opts == 1)
		free_alias(*alias);
	else
	{
		while (arg[i])
		{
			unset_alias(arg[i], alias);
			i++;
		}
	}
	return (0);
}
