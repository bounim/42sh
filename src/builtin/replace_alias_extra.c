/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_alias_extra.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 17:36:57 by khsadira          #+#    #+#             */
/*   Updated: 2019/05/04 17:22:20 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int		check_linked(char **ret, t_alias *alias, t_alias *linked_alias)
{
	t_alias	*head;

	head = linked_alias;
	if (!alias)
		return (0);
	*ret = alias->value;
	while (linked_alias)
	{
		if (ft_strequ(alias->name, linked_alias->name))
		{
			*ret = alias->name;
			return (0);
		}
		linked_alias = linked_alias->next;
	}
	return (1);
}

static t_alias	*add_new_alias(t_alias *linked_alias, char *name, char *value)
{
	t_alias	*new;

	new = new_alias(name, value);
	linked_alias = addlast_alias(linked_alias, new);
	return (linked_alias);
}

char			*find_alias(char *word, t_alias *alias, t_alias *linked_alias, int *lnk)
{
	t_alias	*tmp;
	char	*ret;
	int		i;

	i = 0;
	ret = word;
	tmp = alias;
	while (tmp && i++ < 500)
	{
		if (ft_strequ(tmp->name, word))
		{
			if ((*lnk = check_linked(&ret, tmp, linked_alias)))
			{
				linked_alias = add_new_alias(linked_alias, tmp->name, tmp->value);
				tmp = alias;
				word = ret;
				continue;
			}
			else
			{
				free_alias(linked_alias, 0);
				return (ret);
			}
		}
		tmp = tmp->next;
	}
	free_alias(linked_alias, 0);
	return (ret);
}


static int		is_alias(char *concat, t_alias *alias)
{
	while (alias)
	{
		if (ft_strequ(concat, alias->name))
			return (1);
		alias = alias->next;
	}
	return (0);
}

char			*manage_alias_buff(char *buff, t_alias *alias, int i, int *n)
{
	char	*concat;
	char	*tmp;
	char	*bfr;
	char	*next;
	int		lnk;

	lnk = 1;
	bfr = NULL;
	next = NULL;
	concat = NULL;
	tmp = NULL;
	concat = ft_strsub(buff, i, *n);
	if (is_alias(concat, alias))
	{
		bfr = ft_strsub(buff, 0, i);
		tmp = find_alias(concat, alias, NULL, &lnk);
		next = ft_strsub(buff, i + *n, ft_strlen(buff) - i - *n);
		ft_strdel(&buff);
		buff = ft_strfjoin(bfr, tmp, 0);
		buff = ft_strfjoin(buff, next, 2);
		if (lnk == 1)
			*n = 0;
	}
	ft_strdel(&concat);
	return (buff);
}
