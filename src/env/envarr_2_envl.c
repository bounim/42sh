/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envarr_2_envl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 16:12:19 by schakor           #+#    #+#             */
/*   Updated: 2019/04/22 16:36:44 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

t_envl			*envarr_2_envl(char **env)
{
	t_envl		*ret;
	t_envl		*new;
	char		*ptr;

	ret = NULL;
	if (!env)
		return (ret);
	while (*env != NULL)
	{
		if (!(new = (t_envl *)malloc(sizeof(*new))))
			return (NULL);
		ptr = ft_strchr(*env, '=');
		new->name = ft_strsub(*env, 0, ptr - *env);
		new->value = ft_strsub(*env, ptr - *env + 1, ft_strlen(ptr));
		new->next = NULL;
		if (ft_strcmp(new->name, "SHLVL") == 0)
		{
			ptr = ft_itoa(ft_atoi(new->value) + 1);
			free(new->value);
			new->value = ptr;
		}
		ret = addlast_envl(ret, new);
		env++;
	}
	return (ret);
}
