/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:27:12 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/22 15:07:00 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static char	**from_arg_to_cmd(char **arg, int curr_arg)
{
	int		nb_arg;
	char	**ret;
	int		i;
	int		g_size;

	i = 0;
	ret = NULL;
	nb_arg = curr_arg;
	while (arg[nb_arg])
		nb_arg++;
	g_size = nb_arg - curr_arg;
	if (!(ret = (char **)malloc(sizeof(char *) * (g_size + 1))))
		return (NULL);
	ret[g_size] = NULL;
	while (arg[curr_arg])
	{
		ret[i] = ft_strdup(arg[curr_arg]);
		i++;
		curr_arg++;
	}
	return (ret);
}

static void		exec_env(char **arg, int curr_arg, t_envl *head)
{
	char	**ret;
	char	**env;

	if (!arg[curr_arg])
	{
		print_envl(head, 0);
		free_envl(head);
	}
	else
	{
		ret = from_arg_to_cmd(arg, curr_arg);
		env = envl_to_envarr(head);
		//execution(ret, env);
		ft_free_arr(ret);
		free_envl(head);
	}
}

static int		start_built_env(t_envl *head, char **arg, int last_cmd, int curr_arg)
{
	int		c;
	char	*tmp;
	char	 *tmp2;

	while (arg[curr_arg] && curr_arg != last_cmd)
	{
		if (ft_strequ(arg[curr_arg], "env"))
			return (start_built_env(head, arg, last_cmd, curr_arg + 1));
		else if (ft_strequ(arg[curr_arg], "--"))
			;
		else if (ft_strnequ(arg[curr_arg], "-i", 2))
		{
			free_envl(head);
			return (start_built_env(NULL, arg, last_cmd, curr_arg + 1));
		}
		else if ((c = ft_strichr(arg[curr_arg], '=')))
		{
			tmp = ft_strsub(arg[curr_arg], 0, c);
			tmp2 = ft_strsub(arg[curr_arg], c + 1, ft_strlen(arg[curr_arg]) - c);
			push_env(&head, tmp, tmp2, 1);
			ft_strdel(&tmp);
			ft_strdel(&tmp2);
			return (start_built_env(head, arg, last_cmd, curr_arg + 1));
		}
		curr_arg++;
	}
	exec_env(arg, last_cmd, head);
	return (0);
}

int		built_env(char **arg, t_envl *envl)
{
	int		last_cmd;
	t_envl	*tmp;
	int		ret;
	
	tmp = dup_envl(envl);
	if ((last_cmd = built_env_find_last_cmd(arg)) == -1)
		return (1);
	ret = start_built_env(tmp, arg, last_cmd, 0);
	return (ret);
}
