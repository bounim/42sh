/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 13:43:34 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/22 16:10:05 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

t_history	*find_last_hist_line(void)
{
	t_history *ret;

	if (!(ret = g_shell.hist.history))
		return (NULL);
	while (ret->next)
		ret = ret->next;
	return (ret);
}

t_history	*find_specific_hist_line(int line, t_history *head)
{
	int i;

	i = 1;
	while (i != line && head)
	{
		i++;
		head = head->next;
	}
	if (i == line)
		return (head);
	return (NULL);
}

t_history	*find_first_hist_line(void)
{
	t_history *ret;

	if (!(ret = g_shell.hist.history))
		return (NULL);
	while (ret->bfr)
		ret = ret->bfr;
	return (ret);
}

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
