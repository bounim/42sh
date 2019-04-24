/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:53:32 by emartine          #+#    #+#             */
/*   Updated: 2019/04/18 15:53:33 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions_internal.h"

int		arg_expansions(t_lexer_token *cmd)
{
	t_lexer_token	*cur;

	cur = cmd->arg_head;
	while (cur)
	{
		cur->exp_i = 0;
		if (buffer_expand(cur) < 0)
			return (-1);
		cur = cur->arg_next;
	}
	return (0);
}

int		redir_expansions(t_lexer_token *cmd)
{
	t_lexer_token	*cur;

	cur = cmd->redir_head;
	while (cur)
	{
		cur->exp_i = 0;
		if (cur->rtype != DLESS && cur->rtype != DLESSDASH
				&& buffer_expand(cur->next) < 0)
			return (-1);
		cur = cur->redir_next;
	}
	return (0);
}

int		assign_expansions(t_lexer_token *cmd)
{
	t_lexer_token	*cur;

	cur = cmd->assign_head;
	while (cur)
	{
		cur->exp_i = cur->assign_position + 1;
		buffer_append(cur, cur->buffer, cur->assign_position + 1);
		if (buffer_expand(cur) < 0)
			return (-1);
		cur = cur->assign_next;
	}
	return (0);
}

int		isvarchar(uint8_t ch)
{
	return (ch == '_'
			|| (ch >= '0' && ch <= '9')
			|| (ch >= 'A' && ch <= 'Z')
			|| (ch >= 'a' && ch <= 'z'));
}

int		iswordchar(uint8_t ch)
{
	return (ch != ' ' && ch != '\t' && ch != '\n'
			&& ch != '\\' && ch != '\'' && ch != '\"');
}
