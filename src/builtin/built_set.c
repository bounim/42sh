/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 11:29:37 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/15 14:54:38 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int		built_set(char **arg, t_envl *envl)
{
	if (ft_arrlen(arg) == 3 && ft_strequ(arg[1], "-o"))
	{
		if (ft_strequ(arg[2], "vi"))
			g_shell.el_mode = MODE_VI_INSERT;
		else if (ft_strequ(arg[2], "emacs"))
			g_shell.el_mode = MODE_EMACS;
	}
	else if (ft_arrlen(arg) == 2 && ft_strequ(arg[1], "-o"))
	{
		if (g_shell.el_mode == MODE_EMACS)
			ft_putstr("emacs           on\nvi              off\n");
		else
			ft_putstr("emacs           off\nvi              on\n");
	}
	else
	{
		while (envl)
		{
			ft_putstr(envl->name);
			ft_putchar('=');
			ft_putendl(envl->value);
			envl = envl->next;
		}
	}
	return (0);
}
