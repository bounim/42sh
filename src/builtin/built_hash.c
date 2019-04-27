/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_hash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:11:50 by emartine          #+#    #+#             */
/*   Updated: 2019/04/25 15:16:16 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void		hash_print(t_hashmap_key *k)
{
	printer_bin(&g_shell.out, k->key, k->keysize - 1);
	printer_char(&g_shell.out, '=');
	printer_bin(&g_shell.out, (uint8_t *)k->value, k->valuesize - 1);
	printer_endl(&g_shell.out);
}

static int		hash_list(void)
{
	size_t			i;
	t_hashmap_key	*k;

	i = 0;
	while (i < g_shell.hmap.arraysize)
	{
		if (g_shell.hmap.array[i].key)
		{
			hash_print(g_shell.hmap.array + i);
			k = g_shell.hmap.array[i].next;
			while (k)
			{
				hash_print(k);
				k = k->next;
			}
		}
		i++;
	}
	printer_flush(&g_shell.out);
	return (0);
}

static int		hash_set(char *cmd, t_envl *envl)
{
	size_t	cmdsize;
	char	path[PATH_MAX + 1];

	cmdsize = ft_strlen(cmd) + 1;
	hashmap_unset(&g_shell.hmap, (uint8_t *)cmd, cmdsize);
	if (ft_strchr(cmd, '/') || find_command(path, cmd, envl) != 0)
	{
		printer_str(&g_shell.err, "hash: ");
		printer_str(&g_shell.err, cmd);
		printer_str(&g_shell.err, ": not found\n");
		printer_flush(&g_shell.err);
		return (1);
	}
	return (0);
}

int				built_hash(char **argv, t_envl *envl)
{
	int		r;

	(void)envl;
	if (!argv[1])
		return (hash_list());
	if (argv[1][0] == '-' && argv[1][1] == 'r' && argv[1][2] == '\0')
	{
		hashmap_clean(&g_shell.hmap);
		if (hashmap_init(&g_shell.hmap, HASHMAP_SIZE, hashmap_hash_crc32) < 0)
			fatal_exit(SH_ENOMEM);
		return (1);
	}
	r = 0;
	while (*(++argv))
		r |= hash_set(*argv, envl);
	return (r);
}
