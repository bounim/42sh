/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_envl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 16:36:29 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/22 16:53:39 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	free_envl(t_envl *env)
{
	t_envl	*tmp;

	tmp = NULL;
	while (env)
	{
		ft_strdel(&(env->name));
		ft_strdel(&(env->value));
		tmp = env;
		env = env->next;
		free(tmp);
	}
}
