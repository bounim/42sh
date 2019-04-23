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

static char	*find_command_in_env(char *cmd, size_t size, t_envl *envl)
{
	char			*env_path;
	size_t			start;
	size_t			end;
	char			*ret;
	t_hashmap_key	k;

	if (!(ret = malloc(PATH_MAX + 1))
			|| !(env_path = get_env_val(envl, "PATH")))
		return (NULL);
	start = 0;
	while (env_path[start])
	{
		while (env_path[start] && env_path[start] == ':')
			start++;
		if (!env_path[start])
			return (NULL);
		end = start + 1;
		while (env_path[end] && env_path[end] != ':')
			end++;
		if (end - start + 1 + size <= PATH_MAX)
		{
			ft_memmove(ret, env_path + start, end - start);
			ret[end - start] = '/';
			ft_memmove(ret + end - start + 1, cmd, size);
			ret[end - start + 1 + size] = '\0';
			if (access(ret, X_OK) == 0)
			{
				k.next = NULL;
				k.key = (uint8_t *)cmd;
				k.keysize = size + 1;
				k.value = ret;
				k.valuesize = end - start + 1 + size + 1;
				hashmap_set(&g_shell.hmap, &k);
				return (ret);
			}
		}
		start = end;
	}
	if (ret)
		free(ret);
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
		free(ret);
		return (NULL);
	}
	else
		return (find_command_in_env(cmd, size, envl));
}

char		*command_search(t_lexer_token *cmd, t_envl *envl)
{

	if (cmd->ptype != PARSER_COMMAND || !cmd->argv[0])
	{
		if (!cmd->argv[0])
			fatal_exit(7);
		return (NULL);
	}
	return (find_command(cmd->argv[0], envl));
}