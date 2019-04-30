/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 17:16:41 by emartine          #+#    #+#             */
/*   Updated: 2019/04/24 13:18:14 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include "twenty_one_sh.h"
#include "execution.h"

static int	save_dup(t_lexer_token *cmd, t_lexer_token *cur)
{
	struct stat	sb;

	if (test_fd_new_closed(cmd, cur))
		return (-1);
	if (fstat(cur->fd_saved, &sb) < 0)
	{
		cur->fd_dup = -1;
		if (cur->fd_new == -1)
			return (0);
	}
	else if ((cur->fd_dup = dup(cur->fd_saved)) < 0)
		return (-1);
	if (cur->fd_new == cur->fd_dup)
	{
		close(cur->fd_dup);
		return (-1);
	}
	if (cur->fd_new < 0)
		cur->fd_saved_closed = 1;
	else if (dup2(cur->fd_new, cur->fd_saved) < 0)
	{
		close(cur->fd_dup);
		return (-1);
	}
	return (0);
}

int			error_restore(t_lexer_token *cmd, char *msg)
{
	command_redir_restore(cmd);
	printer_str(&g_shell.err, msg);
	printer_flush(&g_shell.err);
	return (-1);
}

static void	get_fd_saved(t_lexer_token *cur)
{
	if (cur->rtype == LESS || cur->rtype == DLESS || cur->rtype == DLESSDASH
			|| cur->rtype == LESSAND || cur->rtype == LESSGREAT)
		cur->fd_saved = cur->redir_input < 0 ? 0 : cur->redir_input;
	else
		cur->fd_saved = cur->redir_input < 0 ? 1 : cur->redir_input;
}

int			command_redir(t_lexer_token *cmd)
{
	t_lexer_token	*cur;

	cur = cmd->redir_head;
	while (cur)
	{
		get_fd_saved(cur);
		if (redir_op(cmd, cur) < 0)
			return (-1);
		if (save_dup(cmd, cur) < 0)
		{
			if (cur->rtype == LESS || cur->rtype == GREAT
					|| cur->rtype == DGREAT)
				close(cur->fd_new);
			return (error_restore(cmd, "Error: bad file descriptor\n"));
		}
		cmd->redir_last = cur;
		cur = cur->redir_next;
	}
	lazy_close(cmd);
	return (0);
}

void		command_redir_restore(t_lexer_token *cmd)
{
	t_lexer_token	*cur;

	cur = cmd->redir_last;
	while (cur)
	{
		if (!cur->fd_saved_closed)
		{
			if (cur->fd_dup < 0)
				close(cur->fd_saved);
			else
				dup2(cur->fd_dup, cur->fd_saved);
		}
		if (cur->fd_dup > 0)
			close(cur->fd_dup);
		cur = cur->redir_previous;
	}
}
