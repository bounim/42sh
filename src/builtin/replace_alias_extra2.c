/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_alias_extra2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 03:37:19 by khsadira          #+#    #+#             */
/*   Updated: 2019/05/07 03:53:39 by khsadira         ###   ########.fr       */
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

static t_alias	*add_als(t_alias *linked_alias, char *name, char *value)
{
	t_alias	*new;

	new = new_alias(name, value);
	linked_alias = addlast_alias(linked_alias, new);
	return (linked_alias);
}

static int		define_start_alias(char **ret, char *word,
									t_alias **tmp, t_alias *alias)
{
	*ret = word;
	*tmp = alias;
	return (0);
}

static char		*ret_find_alias(char **ret, t_alias **lnk_alias)
{
	free_alias(*lnk_alias, 0);
	return (*ret);
}

char			*find_alias(char *word, t_alias *alias,
							t_alias *lnk_alias, int *lnk)
{
	t_alias	*tmp;
	char	*ret;
	int		i;

	i = define_start_alias(&ret, word, &tmp, alias);
	while (tmp && i++ < 500)
	{
		if (ft_strequ(tmp->name, word))
		{
			if ((*lnk = check_linked(&ret, tmp, lnk_alias)))
			{
				lnk_alias = add_als(lnk_alias, tmp->name, tmp->value);
				tmp = alias;
				word = ret;
				continue;
			}
			else
				return (ret_find_alias(&ret, &lnk_alias));
		}
		tmp = tmp->next;
	}
	return (ret_find_alias(&ret, &lnk_alias));
}
