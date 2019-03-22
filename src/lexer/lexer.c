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

#include <stdio.h> // XXX
#include <unistd.h> // XXX

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

static void			lexer_destroy(t_lexer *lex)
{
	t_lexer_token	*current;
	t_lexer_token	*previous;

	current = lex->head;
	while (current)
	{
		previous = current;
		current = current->next;
		if (previous->type == LEX_TP_WD || previous->type == LEX_TP_OP)
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

	printer_str(&g_shell.out, "lexer_debug:\nbs=");
	printer_int(&g_shell.out, lex->backslash_newline);
	printer_str(&g_shell.out, " qu=");
	printer_int(&g_shell.out, lex->quoted);
	printer_str(&g_shell.out, " nq=");
	printer_int(&g_shell.out, lex->next_quoted);
	printer_str(&g_shell.out, " es=");
	printer_ulong(&g_shell.out, lex->expansion_size);
	printer_endl(&g_shell.out);
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
			printer_str(&g_shell.out, " size=");
			printer_ulong(&g_shell.out, cur->size);
			printer_str(&g_shell.out, " buf='");
			printer_bin(&g_shell.out, cur->buffer, cur->size);
			printer_str(&g_shell.out, "'");
			printer_endl(&g_shell.out);
			cur = cur->next;
		}
	}
	printer_flush(&g_shell.out);
}

static void			test_exec(t_lexer *lex, t_parser *parser)
{
	t_word	*cur;

	if (parser_create_tree(parser, lex) < 0)
		return ;
	if (parser->head == NULL || parser->head->type != PARSER_COMMAND)
		return ;
	printer_str(&g_shell.out, "test exec cmd: ");
	cur = parser->head->arg_head;
	while (cur)
	{
		printer_bin(&g_shell.out, cur->buffer->buf, cur->buffer->size);
		printer_str(&g_shell.out, " ");
		cur = cur->next;
	}
	printer_endl(&g_shell.out);
	printer_flush(&g_shell.out);
}

int 				lexer(void)
{
	t_lexer		lex;
	t_parser	parser;
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
			break ;
		lexer_debug(&lex);
		if (!lex.input_end)
		{
			if (lex.quoted)
				readline(QUOTE_PROMPT);
			else
				readline(BACKSLASH_PROMPT);
			if (!g_shell.line || g_shell.edit.ret_ctrl_c)
				break ;
			i = 0;
			continue ;
		}
		if (lex.head != NULL)
			test_exec(&lex, &parser);
		if (i + lex.i == g_shell.line_size)
			break ;
		i += lex.i;
		lexer_destroy(&lex);
		ft_memset(&lex, 0, sizeof(lex));
	}
	lexer_destroy(&lex);
	return (r);
}
