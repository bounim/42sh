/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unsetenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:30:33 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/02 20:17:18 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static t_envl	*ft_unset(char *word, int size, t_envl *l_env)
{
	t_envl	*h_env;
	t_envl	*tmp;

	if (!ft_memcmp(l_env->name, word, size))
	{
		tmp = l_env->next;
		l_env->next = NULL;
	//	ft_freeenv(l_env);
		return (tmp);
	}
	h_env = l_env;
	while (l_env)
	{
		if (!ft_memcmp(l_env->name, word, size))
		{
			tmp->next = l_env->next;
			l_env->next = NULL;
		//	ft_freeenv(l_env);
			return (h_env);
		}
		tmp = l_env;
		l_env = l_env->next;
	}
	return (h_env);
}

t_envl			*ft_unsetenv(uint8_t **arg, int *arg_size, t_envl *l_env)
{
	int	i;
	int	len;

	len = 0;
	i = 1;
	if (!l_env)
		return (NULL);
	while (arg[len])
		len++;
	if (len < 2)
		ft_putendl_fd("unsetenv: Too few arguments.", 2);
	else
		while (arg[i])
		{
			l_env = ft_unset((char *)arg[i], arg_size[i], l_env);
			i++;
		}
	return (l_env);
}

