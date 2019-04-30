/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:46:18 by emartine          #+#    #+#             */
/*   Updated: 2019/04/24 18:46:25 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"
#include "parser.h"
#include "execution.h"

static int		heredoc_readline(size_t *i)
{
	if (g_shell.line)
	{
		free(g_shell.line);
		g_shell.line = NULL;
	}
	readline(HEREDOC_PROMPT);
	*i = 0;
	if (!g_shell.line || g_shell.edit.ret_ctrl_c)
	{
		g_shell.exit_code = 1;
		free(g_shell.line);
		g_shell.line = NULL;
		return (-1);
	}
	return (0);
}

static int		heredoc_copy(t_lexer_token *heredoc, size_t *i)
{
	uint8_t	*buf;
	size_t	j;

	j = *i;
	while (j < g_shell.line_size && g_shell.line[j] != '\n')
		j++;
	if (j - *i == heredoc->next->size && ft_memcmp(g_shell.line + *i,
				heredoc->next->buffer, heredoc->next->size) == 0)
	{
		*i = j + 1;
		return (0);
	}
	if (NULL == (buf = malloc(heredoc->heredoc_size + j - *i + 1)))
		return (-1);
	ft_memmove(buf, heredoc->heredoc_buffer, heredoc->heredoc_size);
	ft_memmove(buf + heredoc->heredoc_size, g_shell.line + *i, j - *i);
	buf[heredoc->heredoc_size + (j - *i)] = '\n';
	free(heredoc->heredoc_buffer);
	heredoc->heredoc_buffer = buf;
	heredoc->heredoc_size += j - *i + 1;
	*i = j + 1;
	return (1);
}

static int		copy_heredoc_line(t_lexer_token *heredoc, size_t *i)
{
	if (!g_shell.line || *i >= g_shell.line_size)
	{
		if (heredoc_readline(i) < 0)
			return (-1);
	}
	if (*i < g_shell.line_size)
	{
		if (heredoc->rtype == DLESSDASH)
		{
			while (*i < g_shell.line_size && g_shell.line[*i] == '\t')
				(*i)++;
		}
		return (heredoc_copy(heredoc, i));
	}
	return (1);
}

int				read_heredoc(t_lexer *lex, size_t *i)
{
	t_lexer_token	*cur;
	int				r;

	cur = lex->heredoc_head;
	while (cur)
	{
		r = 1;
		while (r > 0)
			r = copy_heredoc_line(cur, i);
		if (r < 0)
			return (-1);
		cur = cur->heredoc_next;
	}
	return (0);
}
