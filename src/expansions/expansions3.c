/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:53:35 by emartine          #+#    #+#             */
/*   Updated: 2019/04/18 15:53:37 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions_internal.h"

static int		not_quoted(t_lexer_token *tok)
{
	size_t	j;
	size_t	k;

	j = tok->exp_i;
	while (j < tok->size && iswordchar(tok->buffer[j]))
		j++;
	if (j > tok->exp_i)
	{
		k = tok->exp_i;
		if ((k == 0 || (tok->assign_position > 0 && k == tok->assign_position
						+ 1)) && tok->buffer[k] == '~')
			k += tilde_expand(tok, j, k);
		var_expand(tok, j, k);
		tok->exp_i = j;
	}
	if (tok->exp_i < tok->size)
	{
		if (tok->buffer[tok->exp_i] == '\\')
			return (1);
		else if (tok->buffer[tok->exp_i] == '\'')
			return (2);
		else if (tok->buffer[tok->exp_i] == '\"')
			return (3);
	}
	return (0);
}

static int		backslash(t_lexer_token *tok)
{
	return (buffer_append(tok, tok->buffer + tok->exp_i, 1) < 0);
}

static int		simple_quote(t_lexer_token *tok)
{
	size_t	j;

	j = tok->exp_i;
	while (j < tok->size && tok->buffer[j] != '\'')
		j++;
	if (j > tok->exp_i)
	{
		if (buffer_append(tok, tok->buffer + tok->exp_i, j - tok->exp_i) < 0)
			return (-1);
		tok->exp_i = j;
	}
	return (0);
}

static int		double_quote(t_lexer_token *tok)
{
	size_t	j;

	j = tok->exp_i;
	while (j < tok->size && tok->buffer[j] != '\"')
	{
		if (tok->buffer[j] == '\\'
				&& j + 1 < tok->size && tok->buffer[j + 1] == '\"')
			break ;
		j++;
	}
	if (j > tok->exp_i)
	{
		var_expand(tok, j, tok->exp_i);
		tok->exp_i = j;
	}
	if (j + 1 < tok->size && tok->buffer[j + 1] == '\"')
	{
		if (buffer_append(tok, (uint8_t *)"\"", 1) < 0)
			return (-1);
		tok->exp_i++;
	}
	return (j < tok->size && tok->buffer[j] == '\"' ? 0 : 3);
}

static int		(*g_exp_func[])(t_lexer_token *) = {
	not_quoted,
	backslash,
	simple_quote,
	double_quote,
};

int				buffer_expand(t_lexer_token *tok)
{
	int		quote;

	quote = 0;
	while (tok->exp_i < tok->size)
	{
		if ((quote = g_exp_func[quote](tok)) < 0)
			return (-1);
		tok->exp_i++;
	}
	if (tok->exp_buffer)
	{
		free(tok->buffer);
		tok->buffer = tok->exp_buffer;
		tok->size = tok->exp_size;
	}
	else
	{
		tok->buffer[0] = '\0';
		tok->size = 0;
	}
	return (0);
}
