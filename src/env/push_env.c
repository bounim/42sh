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

static void		push_env_new(t_envl **head, char *name, char *value_copy,
		int exp)
{
	t_envl		*new;
	char		*name_copy;

	if (NULL == (new = (t_envl *)malloc(sizeof(*new))))
	{
		free(value_copy);
		return ;
	}
	ft_memset(new, 0, sizeof(*new));
	if (NULL == (name_copy = ft_strdup(name)))
	{
		free(value_copy);
		return ;
	}
	new->name = name_copy;
	new->value = value_copy;
	new->exp = exp;
	*head = addlast_envl(*head, new);
}

void			push_env(t_envl **head, char *name, char *value, int exp)
{
	t_envl		*cur;
	char		*value_copy;

	if (!name)
		return ;
	if (NULL == (value_copy = ft_strdup(value)))
		return ;
	cur = *head;
	while (cur)
	{
		if (ft_strcmp(cur->name, name) == 0)
		{
			free(cur->value);
			cur->value = value ? ft_strdup(value) : NULL;
			if (exp && !cur->exp)
				cur->exp = 1;
			free(value_copy);
			return ;
		}
		cur = cur->next;
	}
	push_env_new(head, name, value_copy, exp);
}
