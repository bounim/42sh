/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envl_to_envarr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 18:29:27 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/21 19:34:08 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static char	*memmove_to_arr(char *name, char *value)
{
	int		n_size;
	int		v_size;
	int		g_size;
	char	*ret;

	ret = NULL;
	n_size = ft_strlen(name);
	v_size = ft_strlen(value);
	g_size = n_size + v_size + 1;
	if (!(ret = (char *)malloc(sizeof(char) * g_size + 1)))
		return (NULL);
	ret[g_size] = 0;
	ft_memmove(ret, name, n_size);
	ft_memmove(ret + n_size, "=", 1);
	ft_memmove(ret + n_size + 1, value, v_size);
	return (ret);
}

char		**envl_to_envarr(t_envl *envl)
{
	char	**buff;
	t_envl	*tmp;
	int		i;

	buff = NULL;
	tmp = envl;
	i = 0;
	while (envl)
	{
		if (envl->exp == 1)
			i++;
		envl = envl->next;
	}
	if (!(buff = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	buff[i] = NULL;
	i = 0;
	while (tmp)
	{
		if (tmp->exp == 1)
		{
			buff[i] = memmove_to_arr(tmp->name, tmp->value);
			i++;
		}
		tmp = tmp->next;
	}
	return (buff);
}
