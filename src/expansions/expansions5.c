/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 06:17:02 by emartine          #+#    #+#             */
/*   Updated: 2019/05/07 06:17:03 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions_internal.h"

static char		*tilde_gethome(uint8_t *buffer, size_t size)
{
	char			*home;
	char			login[_POSIX_LOGIN_NAME_MAX + 1];
	struct passwd	*pw;

	if (size == 0)
	{
		if ((home = get_env_val(g_shell.envl, "HOME")) && home[0])
			return (home);
		return (NULL);
	}
	if (size > _POSIX_LOGIN_NAME_MAX)
		return (NULL);
	ft_memmove(login, buffer, size);
	login[size] = '\0';
	if ((pw = getpwnam(login)) && pw->pw_dir && pw->pw_dir[0])
		return (pw->pw_dir);
	return (NULL);
}

size_t			tilde_expand(t_lexer_token *tok, size_t j, size_t k)
{
	char			*home;
	size_t			x;

	x = 1;
	while (x < j && tok->buffer[k + x] != '/' && tok->buffer[k + x] != ':')
		x++;
	if ((home = tilde_gethome(tok->buffer + k + 1, x - 1)))
		buffer_append(tok, (uint8_t *)home, ft_strlen(home));
	else
		buffer_append(tok, tok->buffer + k, x);
	return (x);
}
