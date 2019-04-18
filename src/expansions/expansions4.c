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

int				buffer_append(t_lexer_token *tok, uint8_t *buffer, size_t size)
{
	uint8_t	*r;

	if (NULL == (r = malloc((tok->exp_buffer ? tok->exp_size : 0) + size + 1)))
		return (-1);
	if (tok->exp_buffer)
		ft_memmove(r, tok->exp_buffer, tok->exp_size);
	ft_memmove(r + (tok->exp_buffer ? tok->exp_size : 0), buffer, size);
	r[(tok->exp_buffer ? tok->exp_size : 0) + size] = '\0';
	free(tok->exp_buffer);
	tok->exp_buffer = r;
	tok->exp_size += size;
	return (0);
}

size_t			tilde_expand(t_lexer_token *tok)
{
	char	*home;

	if (NULL == (home = get_env_val(g_shell.envl, "HOME")))
		buffer_append(tok, (uint8_t *)"~", 1);
	else
		buffer_append(tok, (uint8_t *)home, ft_strlen(home));
	return (1);
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
