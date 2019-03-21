/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unsetenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 11:47:45 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/21 17:22:45 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int		unset_env(char *arg, t_envl **envl)
{
	t_envl	*h_env;
	t_envl	*tmp;

	h_env = *envl;
	if (ft_strequ(arg, h_env->name) && h_env->exp == 1)
	{
		*envl = h_env->next;
		h_env->next = NULL;
		free_envl(h_env);
		return (0);
	}
	tmp = h_env;
	h_env = h_env->next;
	while (h_env)
	{
		if (ft_strequ(arg, h_env->name) && h_env->exp == 1)
		{
			tmp->next = h_env->next;
			h_env->next = NULL;
			free_envl(h_env);
			return (0);
			//*envl = head; ????
		}
		tmp = h_env;
		h_env = h_env->next;
	}
	return (1);
}

static int		start_unsetenv(char **arg, t_envl **envl)
{
	int	i;
	int	len;

	len = 0;
	i = 1;
	if (!envl)
		return (1);
	while (arg[len])
		len++;
	if (len < 2)
	{
		ft_putendl_fd("unsetenv: Too few argument", 2);
		return (1);
	}
	while (arg[i])
	{
		unset_env(arg[i], envl);
		i++;
	}
	return (0);
}

int				built_unsetenv(char **arg, t_envl *envl)
{
	if (envl)
	{
		free_envl(g_shell.envl);
		g_shell.envl = envl;
	}
	return (start_unsetenv(arg, &g_shell.envl));
}
