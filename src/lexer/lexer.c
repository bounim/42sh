/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 16:06:31 by emartine          #+#    #+#             */
/*   Updated: 2019/03/21 15:12:48 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"
#include "parser.h"
#include "execution.h"

static int			(*g_lexer_func[])(t_lexer *) = {
	next_quoted,
	line_end,
	unquoted_backslash_newline,
	heredoc,
	operator_append,
	operator_end,
	quoting,
	expansion,
	operator_new,
	unquoted_blank,
	word_append,
	comment,
	word_new,
};

static int			lexer_init(t_lexer *lex, uint8_t *line, size_t line_size)
{
	lex->line = line;
	lex->line_size = line_size;
	lex->i = 0;
	if (lex->init)
	{
		lex->line_y++;
		lex->i = 0;
		lex->backslash_newline = 0;
		lex->input_end = 0;
	}
	else
		lex->init = 1;
	return (0);
}

static int			lexer_read(t_lexer *lex)
{
	size_t	f;
	int		r;

	while (!lex->input_end && lex->i < lex->line_size)
	{
		f = 0;
		while (f < sizeof(g_lexer_func) / sizeof(g_lexer_func[0]))
		{
			if ((r = g_lexer_func[f](lex)) < 0)
				return (r);
			if (r == 0)
				break ;
			f++;
		}
		if (f == sizeof(g_lexer_func) / sizeof(g_lexer_func[0]))
		{
			lex->impl_error = 1;
			return (-1);
		}
		lex->i++;
	}
	return (0);
}

/*
** TODO free heredoc
*/

static void			lexer_destroy(t_lexer *lex)
{
	t_lexer_token	*current;
	t_lexer_token	*previous;

	current = lex->head;
	while (current)
	{
		previous = current;
		current = current->next;
		free(previous->buffer);
		free(previous);
	}
	lex->head = NULL;
	lex->foot = NULL;
}

static int			lexer_work(t_lexer *lex, size_t *i)
{
	if (!lex->input_end)
	{
		if (lex->quoted)
			readline(QUOTE_PROMPT);
		else
			readline(BACKSLASH_PROMPT);
		if (!g_shell.line || g_shell.edit.ret_ctrl_c)
			return (1);
		*i = 0;
		return (-1);
	}
	if (lex->head != NULL)
		test_exec(lex);
	if (*i + lex->i == g_shell.line_size)
		return (1);
	*i += lex->i;
	lexer_destroy(lex);
	ft_memset(lex, 0, sizeof(lex));
	return (0);
}

int					lexer(void)
{
	t_lexer		lex;
	int			r;
	size_t		i;

	if (g_shell.line == NULL || g_shell.line_size <= 1)
		return (0);
	i = 0;
	ft_memset(&lex, 0, sizeof(lex));
	while (1)
	{
		lexer_init(&lex, g_shell.line + i, g_shell.line_size - i);
		if ((r = lexer_read(&lex)) < 0)
		{
			lexer_destroy(&lex);
			break ;
		}
		lexer_debug(&lex);
		if ((r = lexer_work(&lex, &i)))
		{
			if (r < 0)
				continue ;
			break ;
		}
	}
	return (r);
}
