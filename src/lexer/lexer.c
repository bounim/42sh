/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 16:06:31 by emartine          #+#    #+#             */
/*   Updated: 2019/03/12 19:42:16 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

#include <stdio.h> // XXX
#include <unistd.h> // XXX

static int			(*g_lexer_func[])(t_lexer *) = {
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

static void			lexer_destroy(t_lexer *lex)
{
	t_lexer_token	*current;
	t_lexer_token	*previous;

	current = lex->head;
	while (current)
	{
		previous = current;
		current = current->next;
		if (previous->type == TYPE_WORD || previous->type == TYPE_OPERATOR)
			free(previous->buffer);
		// TODO free heredoc
		free(previous);
	}
	lex->head = NULL;
	lex->foot = NULL;
	// TODO destroy parser?
}

static void			lexer_debug(t_lexer *lex)
{
	t_lexer_token	*cur;

	if (lex->head)
	{
		cur = lex->head;
		while (cur)
		{
			printer_str(&g_shell.out, "token=");
			printer_int(&g_shell.out, (int)cur->type);
			printer_str(&g_shell.out, " line_y=");
			printer_ulong(&g_shell.out, cur->line_y);
			printer_str(&g_shell.out, " line_x=");
			printer_ulong(&g_shell.out, cur->line_x);
			printer_str(&g_shell.out, " buf='");
			printer_bin(&g_shell.out, cur->buffer, cur->buffer_size);
			printer_str(&g_shell.out, "'");
			printer_endl(&g_shell.out);
			cur = cur->next;
		}
	}
}

int 				lexer(void)
{
	t_lexer	lex;
	int		r;
	size_t	i;

	r = 0;
	if (g_shell.line == NULL || g_shell.line_size == 0)
		return (0);
	i = 0;
	while (1)
	{
		ft_memset(&lex, 0, sizeof(lex));
		lexer_init(&lex, g_shell.line + i, g_shell.line_size - i);
		if ((r = lexer_read(&lex)) < 0)
			break ;
		if (lex.i < g_shell.line_size - i)
		{
			i += lex.i;
			// TODO call parser
			lexer_debug(&lex);
			lexer_destroy(&lex);
			continue ;
		}
		else if (r == 0)
				break;
		readline(QUOTE_PROMPT);
		if (g_shell.line == NULL || g_shell.line_size == 0)
			break ;
	}
	if (r == 0)
	{
		// TODO call parser
		lexer_debug(&lex);
	}
	lexer_destroy(&lex);
	return (r);
}
