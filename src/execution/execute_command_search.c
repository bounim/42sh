/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_search.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 19:04:49 by kberisha          #+#    #+#             */
/*   Updated: 2019/04/09 22:13:03 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"
#include "execution.h"

static int	test_exec(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) < 0)
		return (1);
	else if ((buf.st_mode & S_IFMT) == S_IFDIR)
		return (2);
	else if (access(path, X_OK) < 0)
		return (3);
	return (0);
}

static int	test_path(char path[PATH_MAX + 1], char *env_path, char *cmd,
		size_t *border)
{
	t_hashmap_key	k;

	ft_memmove(path, env_path + border[0], border[1] - border[0]);
	path[border[1] - border[0]] = '/';
	ft_memmove(path + border[1] - border[0] + 1, cmd, border[2]);
	path[border[1] - border[0] + 1 + border[2]] = '\0';
	if (test_exec(path) != 0)
		return (0);
	k.next = NULL;
	k.key = (uint8_t *)cmd;
	k.keysize = border[2] + 1;
	k.value = path;
	k.valuesize = border[1] - border[0] + 1 + border[2] + 1;
	hashmap_set(&g_shell.hmap, &k);
	return (1);
}

static int	find_command_in_env(char path[PATH_MAX + 1], char *cmd,
		size_t size, t_envl *envl)
{
	char			*env_path;
	size_t			border[3];

	if (!(env_path = get_env_val(envl, "PATH")) || !env_path[0])
		return (-1);
	border[0] = 0;
	border[2] = size;
	while (env_path[border[0]])
	{
		while (env_path[border[0]] && env_path[border[0]] == ':')
			border[0]++;
		if (!env_path[border[0]])
			return (-1);
		border[1] = border[0] + 1;
		while (env_path[border[1]] && env_path[border[1]] != ':')
			border[1]++;
		if (border[1] - border[0] + 1 + size <= PATH_MAX)
		{
			if (test_path(path, env_path, cmd, border))
				return (0);
		}
		border[0] = border[1];
	}
	return (-1);
}

int			find_command(char path[PATH_MAX + 1], char *cmd, t_envl *envl)
{
	size_t			size;
	t_hashmap_key	*k;

	if (!cmd)
		return (-1);
	size = ft_strlen(cmd);
	if (size > PATH_MAX)
		return (-1);
	if ((k = hashmap_get(&g_shell.hmap, (uint8_t *)cmd, size + 1)))
	{
		ft_memmove(path, k->value, k->valuesize);
		return (0);
	}
	if (ft_strchr(cmd, '/'))
	{
		ft_memmove(path, cmd, size + 1);
		return (test_exec(path));
	}
	return (find_command_in_env(path, cmd, size, envl));
}
