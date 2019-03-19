/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 13:43:34 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/19 13:55:35 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

t_history	*rl_new_hist(uint8_t *buf)
{
	t_history	*list;

	if (!(list = (t_history *)malloc(sizeof(*list))))
		return (NULL);
	if (!(list->buf = ft_u8_strdup(buf)))
		return (NULL);
	list->next = NULL;
	list->bfr = NULL;
	return (list);
}

t_history	*rl_add_hist(t_history *list, t_history *new_hist)
{
	if (new_hist == NULL)
	{
		while (list && list->next)
			list = list->next;
		return (list);
	}
	if (list == NULL)
		return (new_hist);
	while (list->next)
		list = list->next;
	list->next = new_hist;
	new_hist->bfr = list;
	return (new_hist);
}
