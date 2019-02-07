/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addlast_envl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 18:11:26 by schakor           #+#    #+#             */
/*   Updated: 2018/11/22 17:42:22 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

t_envl		*addlast_envl(t_envl *head, t_envl *new)
{
	t_envl	*tmp;

	if (head == NULL)
		return (new);
	else if (new == NULL)
		return (head);
	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (head);
}
