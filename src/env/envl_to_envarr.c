/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envl_to_envarr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 18:29:27 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/21 18:53:12 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"
/*
static char	*memmove_to_arr(char *buff, t_envl *envl)
{
	int		n_size;
	int		v_size;
	int		g_size;

	n_size = ft_strlen(envl->name);
	v_size = ft_strlen(envl->value);
	g_size = n_size + v_size + 1;
	if (!(buff = (char *)malloc(sizeof(char) * g_size)))
		return (NULL);
	buff = ft_memmove(buff, envl->name, n_size);
	buff = ft_memmove(buff + n_size, "=", 1);
	buff = ft_memmove(buff + g_size, envl->value, v_size);
	buff[g_size + 1] = '\0';
	printf("%s\n", buff);
	return (buff);
}
*/
char		**envl_to_envarr(t_envl *envl)
{
	char	**buff;
	t_envl	*head;
	int		i;

	buff = NULL;
	head = envl;
	i = 0;
	while (envl)
	{
		if (envl->exp == 1)
			i++;
		envl = envl->next;
	}
	if (!(buff = (char **)malloc(sizeof(char) * i + 1)))
		return (NULL);
	envl = head;
	i = 0;
	while (envl)
	{
	/*	size[0] = ft_strlen(envl->name);
		size[1] = ft_strlen(envl->value);
		if (!(buff[i] = (char *)malloc(sizeof(char) * size[0] + size[1] + 1)))
			return (NULL);
		buff[i] = ft_memmove(buff, envl->name, size[0]);
		buff[i] = ft_memmove(buff + size[0], "=", 1);
		buff[i] = ft_memmove(buff + size[0] + size[1] + 1, envl->value, size[1]);
		buff[i][size[0] + size[1] + 1] = '\0';*/
		if (envl->exp == 1)
		{
			buff[i] = ft_strdup(envl->name);
			buff[i] = ft_strfjoin(buff[i], "=", 0);
			buff[i] = ft_strfjoin(buff[i], envl->value, 0);
			i++;
		}
		envl = envl->next;
	/*	if (envl->exp == 1)
		{
			buff[i] = memmove_to_arr(buff[i], envl);
			i++;
		}
		envl = envl->next;*/
	}
	buff[i] = 0;
	return (buff);
}
