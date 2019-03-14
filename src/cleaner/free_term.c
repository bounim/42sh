/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 21:45:10 by schakor           #+#    #+#             */
/*   Updated: 2019/03/06 15:59:46 by schakor          ###   ########.fr       */
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
		if (tmp)
			free(tmp);
	}
}

void			clean_shell(void)
{
	clean_envl(g_shell.envl);
}
