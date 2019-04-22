/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:53:41 by emartine          #+#    #+#             */
/*   Updated: 2019/04/18 15:53:42 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
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

static size_t	until_dollar_copy(t_lexer_token *tok, size_t j, size_t k)
{
	size_t	x;

	x = 0;
	while (k + x < j && tok->buffer[k + x] != '$')
		x++;
	buffer_append(tok, tok->buffer + k, x);
	return (x);
}

/*
** TODO get env func with memcmp
*/

static size_t	dollar_expand(t_lexer_token *tok, size_t j, size_t k)
{
	size_t	x;
	char	*key;
	char	*val;

	if (k + 1 == j)
	{
		buffer_append(tok, (uint8_t *)"$", 1);
		return (1);
	}
	x = 1;
	if (k + 1 < j && (tok->buffer[k + 1] == '$' || tok->buffer[k + 1] == '?'))
		x++;
	else
		while (k + x < j && isvarchar(tok->buffer[k + x]))
			x++;
	if (NULL == (key = malloc(x)))
		fatal_exit(SH_ENOMEM);
	ft_memmove(key, tok->buffer + k + 1, x - 1);
	key[x - 1] = '\0';
	val = get_env_val(g_shell.envl, key);
	if (val != NULL && val[0] != '\0')
		buffer_append(tok, (uint8_t *)val, ft_strlen(val));
	free(key);
	return (x);
}

void			var_expand(t_lexer_token *tok, size_t j, size_t k)
{
	while (k < j)
	{
		if (tok->buffer[k] != '$')
			k += until_dollar_copy(tok, j, k);
		else
			k += dollar_expand(tok, j, k);
	}
}
