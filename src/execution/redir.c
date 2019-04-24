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
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>
#include "twenty_one_sh.h"
#include "execution.h"
#include "random.h"

static int	save_dup(t_lexer_token *cur)
{
	struct stat	sb;

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
		close(cur->fd_saved);
	else if (dup2(cur->fd_new, cur->fd_saved) < 0)
	{
		close(cur->fd_dup);
		return (-1);
	}
	return (0);
}

static int	copy_path(t_lexer_token *cur, char *path)
{
	if (cur->redir_target->size > PATH_MAX)
		return (-1);
	ft_memmove(path, cur->redir_target->buffer, cur->redir_target->size);
	path[cur->redir_target->size] = '\0';
	return (0);
}

static int	error_restore(t_lexer_token *cmd, char *msg)
{
	command_redir_restore(cmd);
	printer_str(&g_shell.err, msg);
	printer_flush(&g_shell.err);
	return (-1);
}

/*
** TODO heredoc: replace close + open by lseek in 42sh
** lseek(cur->fd_new, 0, SEEK_SET);
*/

int			command_redir(t_lexer_token *cmd)
{
	t_lexer_token	*cur;
	char			path[PATH_MAX + 1];

	cur = cmd->redir_head;
	while (cur)
	{
		if (cur->rtype == LESS || cur->rtype == DLESS || cur->rtype == DLESSDASH
				|| cur->rtype == LESSAND || cur->rtype == LESSGREAT)
			cur->fd_saved = cur->redir_input < 0 ? 0 : cur->redir_input;
		else
			cur->fd_saved = cur->redir_input < 0 ? 1 : cur->redir_input;
		if (cur->rtype == LESS || cur->rtype == GREAT || cur->rtype == DGREAT)
		{
			if (copy_path(cur, path) < 0)
				return (error_restore(cmd, "Error: path too long\n"));
			if (cur->rtype == LESS)
			{
				if ((cur->fd_new = open(path, O_RDONLY)) < 0)
					return (error_restore(cmd, "Error: couldn't open\n"));
			}
			else if ((cur->fd_new = open(path, O_WRONLY | O_CREAT | (cur->rtype
								== GREAT ? O_TRUNC : O_APPEND), 0666)) < 0)
				return (error_restore(cmd, "Error: couldn't open\n"));
		}
		else if (cur->rtype == LESSAND || cur->rtype == GREATAND)
		{
			if (cur->redir_target->buffer[0] == '-')
				cur->fd_new = -1;
			else
				cur->fd_new = ft_memtoi(cur->redir_target->buffer,
						cur->redir_target->size);
		}
		else
		{
			if ((cur->fd_new = random_file(path)) < 0)
				return (error_restore(cmd, "Error: couldn't open\n"));
			if (write(cur->fd_new, cur->heredoc_buffer,
						cur->heredoc_size) != (ssize_t)cur->heredoc_size)
			{
				unlink(path);
				return (error_restore(cmd, "Error: couldn't write\n"));
			}
			close(cur->fd_new);
			cur->fd_new = open(path, O_RDONLY);
			unlink(path);
			if (cur->fd_new < 0)
				return (error_restore(cmd, "Error: couldn't open\n"));
		}
		if (save_dup(cur) < 0)
		{
			if (cur->rtype == LESS || cur->rtype == GREAT
					|| cur->rtype == DGREAT)
				close(cur->fd_new);
			return (error_restore(cmd, "Error: bad file descriptor\n"));
		}
		cmd->redir_last = cur;
		cur = cur->redir_next;
	}
	return (0);
}

void		command_redir_restore(t_lexer_token *cmd)
{
	t_lexer_token	*cur;

	cur = cmd->redir_last;
	while (cur)
	{
		if (cur->fd_saved >= 0)
		{
			if (cur->fd_dup < 0)
				close(cur->fd_saved);
			else
				dup2(cur->fd_dup, cur->fd_saved);
		}
		close(cur->fd_dup);
		cur = cur->redir_previous;
	}
}
