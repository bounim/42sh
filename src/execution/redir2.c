/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:09:18 by emartine          #+#    #+#             */
/*   Updated: 2019/04/24 16:09:19 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>
#include "twenty_one_sh.h"
#include "execution.h"
#include "random.h"

static int	copy_path(t_lexer_token *cur, char *path)
{
	if (cur->redir_target->size > PATH_MAX)
		return (-1);
	ft_memmove(path, cur->redir_target->buffer, cur->redir_target->size);
	path[cur->redir_target->size] = '\0';
	return (0);
}

static int	redir_less_great(t_lexer_token *cmd, t_lexer_token *cur)
{
	char	path[PATH_MAX + 1];

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
	return (0);
}

static void	redir_and(t_lexer_token *cur)
{
	if (cur->redir_target->buffer[0] == '-')
		cur->fd_new = -1;
	else
		cur->fd_new = ft_memtoi(cur->redir_target->buffer,
				cur->redir_target->size);
}

/*
** TODO in heredoc: replace close + open by lseek in 42sh
** lseek(cur->fd_new, 0, SEEK_SET);
** also: unlink path if write fails or after the open/lseek
*/

static int	redir_heredoc(t_lexer_token *cmd, t_lexer_token *cur)
{
	char	path[PATH_MAX + 1];

	if ((cur->fd_new = random_file(path)) < 0)
		return (error_restore(cmd, "Error: couldn't open\n"));
	if (write(cur->fd_new, cur->heredoc_buffer,
				cur->heredoc_size) != (ssize_t)cur->heredoc_size)
	{
		return (error_restore(cmd, "Error: couldn't write\n"));
	}
	close(cur->fd_new);
	cur->fd_new = open(path, O_RDONLY);
	if (cur->fd_new < 0)
		return (error_restore(cmd, "Error: couldn't open\n"));
	return (0);
}

int			redir_op(t_lexer_token *cmd, t_lexer_token *cur)
{
	if (cur->rtype == LESS || cur->rtype == GREAT || cur->rtype == DGREAT)
	{
		if (redir_less_great(cmd, cur) < 0)
			return (-1);
	}
	else if (cur->rtype == LESSAND || cur->rtype == GREATAND)
		redir_and(cur);
	else
	{
		if (redir_heredoc(cmd, cur) < 0)
			return (-1);
	}
	return (0);
}
