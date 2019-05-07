/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 06:02:21 by emartine          #+#    #+#             */
/*   Updated: 2019/05/07 06:02:22 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

char		**arg_to_argv(t_lexer_token *cmd)
{
	size_t			i;
	t_lexer_token	*cur;
	char			**av;

	if (!cmd->arg_head)
		return (NULL);
	if (NULL == (av = (char **)malloc((cmd->arg_nb + 1) * sizeof(*av))))
		return (NULL);
	i = 0;
	cur = cmd->arg_head;
	while (i < cmd->arg_nb)
	{
		av[i] = (char *)cur->buffer;
		i++;
		cur = cur->arg_next;
	}
	av[cmd->arg_nb] = NULL;
	return (av);
}
