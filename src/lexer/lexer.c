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

#include "twenty_one_sh.h"
#include "lexer_internal.h"

static int			(*g_lexer_func[])(t_lexer *) = {
	next_quoted,
	line_end,
	unquoted_backslash_newline,
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
			return (-1);
		lex->i++;
	}
	return (0);
}

/*
** TODO free heredoc
*/

void				lexer_destroy(t_lexer *lex)
{
	t_lexer_token	*current;
	t_lexer_token	*previous;

	if (!lex)
		return ;
	current = lex->head;
	while (current)
	{
		previous = current;
		current = current->next;
		free(previous->buffer);
		free(previous->heredoc_buffer);
		free(previous);
	}
	ft_memset(lex, 0, sizeof(*lex));
}

void				lexer(t_lexer *lex, uint8_t *buffer, size_t buffer_size)
{
	lexer_init(lex, buffer, buffer_size);
	if (lexer_read(lex) < 0)
	{
		printer_str(&g_shell.err, "Error: lexer: out of memory\n");
		printer_flush(&g_shell.err);
		lexer_destroy(lex);
		fatal_exit(SH_ENOMEM);
		return ;
	}
	lexer_debug(lex);
}
