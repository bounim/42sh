/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_alias_extra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:35:23 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/29 16:51:00 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int			free_alias(t_alias *alias, int a)
{
	t_alias	*tmp;

	tmp = NULL;
	while (alias)
	{
		ft_strdel(&(alias->name));
		ft_strdel(&(alias->value));
		tmp = alias;
		alias = alias->next;
		free(tmp);
	}
	if (a == 1)
		g_shell.alias = NULL;
	return (0);
}

int			print_alias(t_alias *alias)
{
	while (alias)
	{
		ft_putstr("alias ");
		ft_putstr(alias->name);
		ft_putchar('=');
		ft_putstr(alias->value);
		ft_putchar(10);
		alias = alias->next;
	}
	return (0);
}

t_alias		*new_alias(char *name, char *value)
{
	t_alias	*new;

	if (!(new = (t_alias *)malloc(sizeof(*new))))
		return (NULL);
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

void		push_alias(t_alias **alias, char *name, char *value)
{
	t_alias	*tmp;

	tmp = NULL;
	if (!alias || !name || !value)
		return ;
	tmp = *alias;
	if (tmp)
	{
		while (tmp->next != NULL)
		{
			if (ft_strequ(tmp->name, name))
			{
				ft_strdel(&tmp->value);
				tmp->value = ft_strdup(value);
				return ;
			}
			tmp = tmp->next;
		}
	}
	if (!(tmp = (t_alias *)malloc(sizeof(*tmp))))
		return ;
	tmp->name = ft_strdup(name);
	tmp->value = ft_strdup(value);
	tmp->next = NULL;
	*alias = addlast_alias(*alias, tmp);
}

t_alias		*addlast_alias(t_alias *head, t_alias *new)
{
	t_alias	*tmp;

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
