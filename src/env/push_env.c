/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:30:17 by schakor           #+#    #+#             */
/*   Updated: 2019/03/21 15:34:24 by khsadira         ###   ########.fr       */
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
				if (tmp->read_only == 1)
				{
					ft_putstr_fd("env: ", 2);
					ft_putstr_fd(tmp->name, 2);
					ft_putstr_fd(": is set as READ_ONLY\n", 2);
					return ;
				}
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
	tmp->read_only = 0;
	tmp->next = NULL;
	*head = addlast_envl(*head, tmp);
}
