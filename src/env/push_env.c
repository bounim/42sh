/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:30:17 by schakor           #+#    #+#             */
/*   Updated: 2019/04/09 16:41:59 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void			push_env(t_envl **head, char *name, char *value, int exp)
{
	t_envl		*tmp;

	tmp = NULL;
	if (!*head || !name)
		return ;
	tmp = *head;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			free(tmp->value);
			tmp->value = value ? ft_strdup(value) : NULL;
			if (exp && !tmp->exp)
				tmp->exp = 1;
			return ;
		}
		tmp = tmp->next;
	}
	if (!(tmp = (t_envl *)malloc(sizeof(*tmp))))
		return ;
	ft_memset(tmp, 0, sizeof(*tmp));
	tmp->name = ft_strdup(name);
	tmp->value = value ? ft_strdup(value) : NULL;
	tmp->exp = exp;
	*head = addlast_envl(*head, tmp);
}
