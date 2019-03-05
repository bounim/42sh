/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:27:12 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/04 17:15:25 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static char	**from_arg_to_cmd(uint8_t **arg, int *arg_size, int curr_arg)
{
	int		nb_arg;
	char	**ret;
	int		i;
	char	*tmp;

	i = 0;
	nb_arg = curr_arg;
	while (arg[nb_arg])
		nb_arg++;
	if (!(ret = (char **)malloc(sizeof(char *) * 	nb_arg)))
		return (NULL);
	while (ret[i] && arg[curr_arg])
	{
		tmp = ft_memalloc(arg_size[curr_arg]);
		tmp = ft_memcpy(tmp, arg[curr_arg], arg_size[curr_arg]);
		ret[i] = tmp;
		i++;
		curr_arg++;
	}
	return (ret);
}

static void		exec_env(uint8_t **arg, int *arg_size, int curr_arg, t_envl *head)
{
	char	**ret;
	(void)head;
	if (!arg[curr_arg])
	{
		//print_env(head);
		//free_env(head);
	}
	else
	{
		ret = from_arg_to_cmd(arg, arg_size, curr_arg);
		//execution;
		//free_tab;
		//free_env;
	}
}

static int		my_memchr_w(uint8_t *arg, int c, int arg_size)
{
	int		i;
	
	i = 0;
	while (i < arg_size)
	{
		if (arg[i] == c)
			return (i);
		i++;
	}
	if (arg[i] == c)
		return (i);
	return (-1);
}

int		built_env(t_envl *head, uint8_t **arg, int *arg_size, int last_cmd, int curr_arg)
{
	int		c;
	uint8_t	*tmp;
	uint8_t *tmp2;

	while (arg[curr_arg] && curr_arg != last_cmd)
	{
		if (ft_memcmp(arg[curr_arg], "env\0", 4))
			return (built_env(head, arg, arg_size, last_cmd, curr_arg + 1));
		else if (ft_memcmp(arg[curr_arg], "-i", 2))
		{
			//free env;
			return (built_env(head, arg, arg_size, last_cmd, curr_arg + 1));
		}
		else if ((c = my_memchr_w(arg[curr_arg], '=', arg_size[curr_arg])) != -1)
		{
			tmp = ft_memalloc(c);
			tmp = ft_memcpy(tmp, arg[curr_arg], c);
			tmp2 = ft_memalloc(arg_size[curr_arg] - c);
			tmp2 = ft_memcpy(tmp2, arg[curr_arg] + c, arg_size[curr_arg] - c);
			push_env(&head, (char *)tmp, (char *)tmp2);
			//free tmp & tmp2 ??
			return (built_env(head, arg, arg_size, last_cmd, curr_arg + 1));
		}
		curr_arg++;
	}
	exec_env(arg, arg_size, curr_arg, head);
	return (ENV_OK);
}
//built_env_check_error +  return last cmd;
//send dulicate env to built_env 
