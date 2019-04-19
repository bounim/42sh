/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:21:23 by kberisha          #+#    #+#             */
/*   Updated: 2019/04/09 16:54:50 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions_internal.h"

int				command_expansions(t_lexer_token *cmd)
{
	if (!cmd || cmd->ptype != PARSER_COMMAND)
		return (0);
	if (arg_expansions(cmd) < 0
			|| redir_expansions(cmd) < 0
			|| assign_expansions(cmd) < 0)
		return (-1);
	return (0);
}

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
