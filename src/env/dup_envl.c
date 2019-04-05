/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_envl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 16:08:18 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/05 18:42:05 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

t_envl	*dup_envl(t_envl *env)
{
	t_envl	*new;
	t_envl	*head;
	t_envl	*tmp;

	tmp = NULL;
	head = NULL;
	tmp = env;
	while (tmp)
	{
		if (!(new = (t_envl *)malloc(sizeof(t_envl))))
			return (NULL);
		new->name = ft_strdup(tmp->name);
		new->value = ft_strdup(tmp->value);
		new->exp = tmp->exp;
		new->read_only = tmp->read_only;
		new->next = NULL;
		head = addlast_envl(head, new);
		tmp = tmp->next;
	}
	return (head);
}
