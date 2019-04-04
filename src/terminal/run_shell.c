/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:20:17 by emartine          #+#    #+#             */
/*   Updated: 2019/04/02 18:20:18 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"
#include "parser.h"
#include "execution.h"

// TODO set $* accordingly (0 or 1 if ^C)
static void		lex_a_line(t_lexer *lex, enum e_prompt prompt, size_t *i)
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
	//if (lex->last_parsed) // TODO op prompt
	return (BACKSLASH_PROMPT);
}

/*static int		copy_heredoc(t_lexer *lex, uint8_t *buffer, size_t buffer_size)
{
	// TODO
	(void)lex;
	(void)buffer;
	(void)buffer_size;
	return 42;
}*/

static void		read_heredoc(t_lexer *lex, size_t *i)
{
	// TODO exit if malloc fails
	/*if (!lex->heredoc_head)
		return (0);
	// TODO
	//readline(HEREDOC_PROMPT);
	//if (copy_heredoc(lex, g_shell.line + *i, g_shell.line_size - *i) < 0)
	// TODO heredoc_current
	return (-1);*/
	(void)lex;
	(void)i;
	if (!lex->heredoc_head)
		return ;
}

void			run_shell(void)
{
	t_lexer		lex;
	size_t		i;

	// FIXME useful?
	if (signal(SIGINT, ft_signal) < 0)
		fatal_exit(SH_EINVAL);
	if (signal(SIGABRT, ft_signal) < 0)
		fatal_exit(SH_EINVAL);
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
		read_heredoc(&lex, &i);
		execution(&lex);
		lexer_destroy(&lex);
	}
}
