/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 16:25:32 by emartine          #+#    #+#             */
/*   Updated: 2019/04/30 16:25:33 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "twenty_one_sh.h"
#include "execution.h"

int			will_close(t_lexer_token *cmd, int fd)
{
	t_lexer_token	*cur;

	cur = cmd->redir_last;
	while (cur)
	{
		if (cur->fd_saved == fd && cur->fd_saved_closed)
			return (1);
		cur = cur->redir_previous;
	}
	return (0);
}

void		lazy_close(t_lexer_token *cmd)
{
	t_lexer_token	*cur;

	cur = cmd->redir_head;
	while (cur)
	{
		if (cur->fd_saved_closed)
		{
			close(cur->fd_saved);
			cur->fd_saved_closed = 0;
		}
		cur = cur->redir_next;
	}
}

int			test_fd_new_closed(t_lexer_token *cmd, t_lexer_token *cur)
{
	struct stat	sb;

	if (cur->fd_new >= 0
			&& (will_close(cmd, cur->fd_new) || fstat(cur->fd_new, &sb) < 0))
		return (1);
	return (0);
}

void		close_fd_before_exec(t_lexer_token *cmd)
{
	t_lexer_token	*cur;

	cur = cmd->redir_head;
	while (cur)
	{
		if (cur->fd_dup > 0)
			close(cur->fd_dup);
		cur = cur->redir_next;
	}
}
