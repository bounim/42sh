/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:27:12 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/12 17:08:38 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static char	**from_lenv_to_tab(t_envl *head)
{
	char	**ret;
	t_envl	*tmp;
	int		i;
	char	*buf;

	i = 0;
	ret = NULL;
	tmp = head;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	if (!(ret = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	tmp = head;
	buf = ft_strdup("");
	i = 0;
	while (tmp)
	{
		buf = ft_strfjoin(buf, tmp->name, 0);
		buf = ft_strfjoin(buf, tmp->value, 0);
		///if (!(ret[i] = (char *)malloc(sizeof(char) * ft_strlen(buf))))
		//	return (NULL);
		ret[i] = buf;
		i++;
		tmp = tmp->next;
	}
	return (ret);
}

static char	**from_arg_to_cmd(char **arg, int curr_arg)
{
	int		nb_arg;
	char	**ret;
	int		i;
	char	*tmp;

	i = 0;
	nb_arg = curr_arg;
	while (arg[nb_arg])
		nb_arg++;
	if (!(ret = (char **)malloc(sizeof(char *) * nb_arg)))
		return (NULL);
	while (ret[i] && arg[curr_arg])
	{
		tmp = ft_memalloc(ft_strlen(arg[curr_arg]));
		tmp = ft_memcpy(tmp, arg[curr_arg], ft_strlen(arg[curr_arg]));
		ret[i] = tmp;
		i++;
		curr_arg++;
	}
	return (ret);
}

static void		exec_env(char **arg, int curr_arg, t_envl *head)
{
	char	**ret;
	int		i;
	char	**env;

	i = 0;
	if (!arg[curr_arg])
	{
		print_envl(head);
		free_envl(head);
	}
	else
	{
		ret = from_arg_to_cmd(arg, curr_arg);
		while (ret[i])
			ft_strdel(&ret[i++]);
		free(ret);
		free_envl(head);
		env = from_lenv_to_tab(head);
		//execution(ret, env);
		i = 0;
		while (ret[i])
			ft_strdel(&ret[i++]);
		free(ret);
	}
}

static int		start_built_env(t_envl *head, char **arg, int last_cmd, int curr_arg)
{
	int		c;
	char	*tmp;
	char	 *tmp2;

	while (arg[curr_arg] && curr_arg != last_cmd)
	{
		if (ft_strcmp(arg[curr_arg], "env"))
			return (start_built_env(head, arg, last_cmd, curr_arg + 1));
		else if (ft_strcmp(arg[curr_arg], "-i"))
		{
			free_envl(head);
			return (start_built_env(head, arg, last_cmd, curr_arg + 1));
		}
		else if ((c = ft_strichr(arg[curr_arg], '=')))
		{
			tmp = ft_strsub(arg[curr_arg], 0, c);
			tmp2 = ft_strsub(arg[curr_arg], c + 1, ft_strlen(arg[curr_arg]) - c);
			push_env(&head, tmp, tmp2);
			ft_strdel(&tmp);
			ft_strdel(&tmp2);
			return (start_built_env(head, arg, last_cmd, curr_arg + 1));
		}
		curr_arg++;
	}
	exec_env(arg, curr_arg, head);
	return (0);
}

int		built_env(t_envl *env, char **arg)
{
	int		last_cmd;
	t_envl	*tmp;
	
	tmp = NULL;
	last_cmd = built_env_find_last_cmd(arg);
	tmp = dup_envl(env);
	return (start_built_env(tmp, arg, last_cmd, 0));
}
