/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_alias_extra.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 03:37:48 by khsadira          #+#    #+#             */
/*   Updated: 2019/05/07 04:16:05 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

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

static void		set_variable(char **concat, char *tmp, int *i, int *n)
{
	int		len;

	if (tmp)
	{
		len = ft_strlen(tmp);
		if (len >= 1 && (tmp[len - 1] == ' ' || tmp[len - 1] == '\t'))
		{
			*i += len;
			*n = 0;
		}
	}
	ft_strdel(concat);
	return ;
}

char			*manage_alias_buff(char *buff, t_alias *alias, int *i, int *n)
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
	concat = ft_strsub(buff, *i, *n);
	if (is_alias(concat, alias))
	{
		bfr = ft_strsub(buff, 0, *i);
		tmp = find_alias(concat, alias, NULL, &lnk);
		next = ft_strsub(buff, *i + *n, ft_strlen(buff) - *i - *n);
		ft_strdel(&buff);
		buff = ft_strfjoin(bfr, tmp, 0);
		buff = ft_strfjoin(buff, next, 2);
		if (!ft_strnequ(buff, concat, ft_strlen(concat)) && lnk == 1)
			*n = 0;
	}
	set_variable(&concat, tmp, i, n);
	return (buff);
}
