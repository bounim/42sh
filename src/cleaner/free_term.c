/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 21:45:10 by schakor           #+#    #+#             */
/*   Updated: 2018/12/18 16:32:17 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void			clean_envl(t_envl *list)
{
	t_envl		*tmp;

	while (list)
	{
		free(list->name);
		free(list->value);
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

void			clean_shell(t_shell *sh)
{
	if (sh)
	{
		printer_flush(&g_shell->out);
		printer_flush(&g_shell->err);
		reset_terminal(sh);
		ft_arrdel(sh->env);
		clean_envl(sh->envl);
		free(sh);
	}
}
