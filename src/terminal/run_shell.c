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

static void				run_shell_loop(t_lexer *lex, size_t *i)
{
	while (1)
	{
		while (!lex->input_end)
			lex_a_line(lex, determine_prompt(lex), i);
		if (parser_create_tree(lex) < 0)
		{
			lexer_destroy(lex);
			continue ;
		}
		if (!parser_input_end(lex))
		{
			lex->input_end = 0;
			continue ;
		}
		if (read_heredoc(lex, i) < 0)
		{
			lexer_destroy(lex);
			continue ;
		}
		execute(lex);
		lexer_destroy(lex);
		free_exec();
	}
}

void					run_shell(void)
{
	t_lexer		lex;
	size_t		i;

	ft_memset(&lex, 0, sizeof(lex));
	g_shell.lexer = &lex;
	i = 0;
	run_shell_loop(&lex, &i);
}
