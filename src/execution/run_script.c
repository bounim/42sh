/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_script.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 03:18:05 by emartine          #+#    #+#             */
/*   Updated: 2019/05/07 03:18:07 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int				copy_heredoc_line(t_lexer_token *heredoc, size_t *i,
		uint8_t *buf, size_t size)
{
	if (*i >= size)
	{
		write_error("syntax error", "unexpected end of file");
		return (-1);
	}
	if (heredoc->rtype == DLESSDASH)
	{
		while (*i < size && buf[*i] == '\t')
			(*i)++;
	}
	return (script_heredoc_copy(heredoc, i, buf, size));
}

static int				read_script_heredoc(t_lexer *lex, size_t *i,
		uint8_t *buf, size_t size)
{
	t_lexer_token	*cur;
	int				r;

	cur = lex->heredoc_head;
	while (cur)
	{
		r = 1;
		while (r > 0)
			r = copy_heredoc_line(cur, i, buf, size);
		if (r < 0)
			return (-1);
		cur = cur->heredoc_next;
	}
	return (0);
}

static int				run_script_work_end(t_lexer *lex, size_t *i,
		uint8_t *buf, size_t size)
{
	if (!parser_input_end(lex))
	{
		lex->input_end = 0;
		return (-1);
	}
	if (read_script_heredoc(lex, i, buf, size) < 0)
	{
		lexer_destroy(lex);
		return (-1);
	}
	return (0);
}

static void				run_script_work(t_lexer *lex, size_t *i,
		uint8_t *buf, size_t size)
{
	size_t	i_old;

	while (1)
	{
		i_old = *i;
		while (!lex->input_end)
		{
			if (script_lex_a_line(lex, i, buf, size) < 0)
				return ;
		}
		if (parser_create_tree(lex) < 0)
		{
			lexer_destroy(lex);
			continue ;
		}
		if (run_script_work_end(lex, i, buf, size) < 0)
			continue;
		write(2, buf + i_old, *i - i_old);
		execute(lex);
		lexer_destroy(lex);
	}
}

void					run_script(uint8_t *buf)
{
	size_t	size;
	t_lexer	lex;
	size_t	i;

	if (!buf)
		return ;
	ft_memset(&lex, 0, sizeof(lex));
	g_shell.script_lexer = &lex;
	i = 0;
	size = ft_strlen((char *)buf);
	run_script_work(&lex, &i, buf, size);
	free(buf);
	g_shell.script_lexer = NULL;
}
