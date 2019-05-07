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

#include "expansions_internal.h"

static size_t	until_dollar_copy(t_lexer_token *tok, size_t j, size_t k)
{
	size_t	x;

	x = 0;
	while (k + x < j && tok->buffer[k + x] != '$')
		x++;
	buffer_append(tok, tok->buffer + k, x);
	return (x);
}

static size_t	replace_braces(t_lexer_token *tok, size_t j, size_t k)
{
	size_t	x;
	char	*key;
	char	*val;

	x = 0;
	while (k + x < j && tok->buffer[k + x] != '}')
		x++;
	if (NULL == (key = malloc(x)))
		fatal_exit(SH_ENOMEM);
	ft_memmove(key, tok->buffer + k + 1, x - 1);
	key[x - 1] = '\0';
	val = get_env_val(g_shell.envl, key);
	if (val != NULL && val[0] != '\0')
		buffer_append(tok, (uint8_t *)val, ft_strlen(val));
	free(key);
	return (x + 2);
}

static size_t	dollar_expand_end(t_lexer_token *tok, size_t k, size_t x)
{
	char	*key;
	char	*val;

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

static size_t	dollar_expand(t_lexer_token *tok, size_t j, size_t k)
{
	size_t	x;

	if (k + 1 == j)
	{
		buffer_append(tok, (uint8_t *)"$", 1);
		return (1);
	}
	x = 1;
	if (k + 1 < j && (tok->buffer[k + 1] == '$' || tok->buffer[k + 1] == '?'))
		x++;
	else if (tok->buffer[k + 1] == '{')
		return (replace_braces(tok, j, k + 1));
	else
		while (k + x < j && isvarchar(tok->buffer[k + x]))
			x++;
	return (dollar_expand_end(tok, k, x));
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
