/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:30:17 by schakor           #+#    #+#             */
/*   Updated: 2019/03/13 10:53:46 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void			push_env(t_envl **head, char *name, char *value, int exp)
{
	t_envl		*tmp;

	tmp = NULL;
	if (!head || !name || !value)
		return ;
	tmp = *head;
	if (tmp)
	{
		while (tmp->next != NULL)
		{
			if (ft_strcmp(tmp->name, name) == 0)
			{
				free(tmp->value);
				tmp->value = ft_strdup(value);
				tmp->exp = exp;
				return ;
			}
			tmp = tmp->next;
		}
	}
	if (!(tmp = (t_envl *)malloc(sizeof(*tmp))))
		return ;
	tmp->name = ft_strdup(name);
	tmp->value = ft_strdup(value);
	tmp->exp = exp;
	tmp->next = NULL;
	*head = addlast_envl(*head, tmp);
}
