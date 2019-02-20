/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_val.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 18:52:56 by schakor           #+#    #+#             */
/*   Updated: 2018/11/10 19:29:27 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

char		*get_env_val(t_envl *envl, char *name)
{
	if (envl == NULL || name == NULL)
		return (NULL);
	while (envl != NULL)
	{
		if (envl->name != NULL && ft_strcmp(envl->name, name) == 0)
			return (envl->value);
		envl = envl->next;
	}
	return (NULL);
}
