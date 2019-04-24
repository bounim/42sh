/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:20:17 by emartine          #+#    #+#             */
/*   Updated: 2019/04/24 13:12:45 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"
#include "parser.h"
#include "execution.h"

static void				lex_a_line(t_lexer *lex, enum e_prompt prompt,\
		size_t *i)
{
	while (1)
	{
		if (g_shell.line && *i < g_shell.line_size)
		{
			lexer(lex, g_shell.line + *i, g_shell.line_size - *i);
			*i += lex->i;
			return ;
		}
		else
		{
			if (g_shell.line)
			{
				free(g_shell.line);
				g_shell.line = NULL;
			}
			readline(prompt);
			if (!g_shell.line || g_shell.edit.ret_ctrl_c)
			{
				g_shell.exit_code = 1;
				lexer_destroy(lex);
				prompt = BASIC_PROMPT;
			}
			*i = 0;
		}
	}
}

static enum e_prompt	determine_prompt(t_lexer *lex)
{
	if (!lex->init || !lex->head)
		return (BASIC_PROMPT);
	if (lex->quoted)
		return (QUOTE_PROMPT);
	return (BACKSLASH_PROMPT);
}

static int				copy_heredoc_line(t_lexer_token *heredoc, size_t *i)
{
	size_t	j;
	uint8_t	*buf;

	if (!g_shell.line || *i >= g_shell.line_size)
	{
		readline(HEREDOC_PROMPT);
		*i = 0;
		if (!g_shell.line || g_shell.edit.ret_ctrl_c)
		{
			g_shell.exit_code = 1;
			free(g_shell.line);
			g_shell.line = NULL;
			return (-1);
		}
	}
	if (*i < g_shell.line_size)
	{
		if (heredoc->rtype == DLESSDASH)
		{
			while (*i < g_shell.line_size && g_shell.line[*i] == '\t')
				(*i)++;
		}
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
	return (1);
}

static int				read_heredoc(t_lexer *lex, size_t *i)
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

void					run_shell(void)
{
	t_lexer		lex;
	size_t		i;

	ft_memset(&lex, 0, sizeof(lex));
	i = 0;
	while (1)
	{
		while (!lex.input_end)
			lex_a_line(&lex, determine_prompt(&lex), &i);
		if (parser_create_tree(&lex) < 0)
		{
			lexer_destroy(&lex);
			continue ;
		}
		if (!parser_input_end(&lex))
		{
			lex.input_end = 0;
			continue ;
		}
		if (read_heredoc(&lex, &i) < 0)
		{
			lexer_destroy(&lex);
			continue ;
		}
		execute(&lex);
		lexer_destroy(&lex);
	}
}
