/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:28:52 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/05 15:18:41 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int			built_history(char **arg, t_envl *envl)
{
	int		len;

	(void)envl;
	if (!g_shell.hist.history)
		return (1);
	if ((len = ft_arrlen(arg)) >= 1)
	{
		print_historyl(g_shell.hist.history);
		return (0);
	}
	return (1);
}
