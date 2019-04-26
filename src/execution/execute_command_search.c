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

#include <limits.h>
#include "twenty_one_sh.h"
#include "execution.h"

static int	init_hash(char *ret, size_t *border, char *cmd, size_t size)
{
	t_hashmap_key	k;

	if (access(ret, X_OK) == 0)
	{
		k.next = NULL;
		k.key = (uint8_t *)cmd;
		k.keysize = size + 1;
		k.value = ret;
		k.valuesize = border[1] - border[0] + 1 + size + 1;
		hashmap_set(&g_shell.hmap, &k);
		return (1);
	}
	return (0);
}

static char	*test_access(char *env_path, char *cmd, size_t *border, size_t size)
{
	char			*ret;

	ret = NULL;
	if (!(ret = malloc(PATH_MAX + 1)))
		return (NULL);
	ft_memmove(ret, env_path + border[0], border[1] - border[0]);
	ret[border[1] - border[0]] = '/';
	ft_memmove(ret + border[1] - border[0] + 1, cmd, size);
	ret[border[1] - border[0] + 1 + size] = '\0';
	if (init_hash(ret, border, cmd, size))
		return (ret);
	free(ret);
	return (NULL);
}

static char	*find_command_in_env(char *cmd, size_t size, t_envl *envl)
{
	char			*env_path;
	char			*r;
	size_t			border[2];

	if (!(env_path = get_env_val(envl, "PATH")))
		return (NULL);
	border[0] = 0;
	while (env_path[border[0]])
	{
		while (env_path[border[0]] && env_path[border[0]] == ':')
			border[0]++;
		if (!env_path[border[0]])
			return (NULL);
		border[1] = border[0] + 1;
		while (env_path[border[1]] && env_path[border[1]] != ':')
			border[1]++;
		if (border[1] - border[0] + 1 + size <= PATH_MAX)
		{
			if ((r = test_access(env_path, cmd, border, size)))
				return (r);
		}
		border[0] = border[1];
	}
	return (NULL);
}

char		*find_command(char *cmd, t_envl *envl)
{
	char			*ret;
	size_t			size;
	t_hashmap_key	*k;

	size = ft_strlen(cmd);
	if (size > PATH_MAX)
		return (NULL);
	if ((k = hashmap_get(&g_shell.hmap, (uint8_t *)cmd, size + 1)))
		return (ft_strdup((char *)k->value));
	if (ft_strchr(cmd, '/'))
	{
		if (!(ret = malloc(PATH_MAX + 1)))
			return (NULL);
		ft_memmove(ret, cmd, size);
		ret[size] = '\0';
		if (access(ret, X_OK) == 0)
			return (ret);
		return (NULL);
	}
	else
		return (find_command_in_env(cmd, size, envl));
}

char		*command_search(t_lexer_token *cmd, char **arg, t_envl *envl)
{
	if (cmd->ptype != PARSER_COMMAND || !arg[0])
	{
		if (!arg[0])
			fatal_exit(7);
		return (NULL);
	}
	return (find_command(arg[0], envl));
}
