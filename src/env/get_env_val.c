/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_val.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 18:52:56 by schakor           #+#    #+#             */
/*   Updated: 2019/04/10 14:52:04 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static char	*savepid(void)
{
	pid_t	pid;
	size_t	i;

	i = 1;
	pid = getpid();
	while (pid > 9)
	{
		i++;
		pid /= 10;
	}
	pid = getpid();
	g_shell.pid_buffer[i] = '\0';
	while (i--)
	{
		g_shell.pid_buffer[i] = '0' + pid % 10;
		pid /= 10;
	}
	return (g_shell.pid_buffer);
}

char		*get_env_val(t_envl *envl, char *name)
{
	if (!envl || !name)
		return (NULL);
	if (name[0] == '$' && name[1] == '\0')
		return (savepid());
	while (envl != NULL)
	{
		if (envl->name != NULL && ft_strcmp(envl->name, name) == 0)
			return (envl->value);
		envl = envl->next;
	}
	return (NULL);
}
