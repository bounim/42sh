/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:20:17 by emartine          #+#    #+#             */
/*   Updated: 2019/04/04 18:35:58 by khsadira         ###   ########.fr       */
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

/*
static void test_job(void)
{
	t_job	*new_job;
	t_proc	*new_proc;

	printf("je suis la \n");
	new_job = NULL;
	new_proc = NULL;
	new_job = creat_job("ls -l | wc | pwd");
	char *arg[3] = {"ls", "-l", NULL};
	new_proc = creat_proc(arg, g_shell.envl, "/bin/ls");
	new_job->head_proc = add_proc(new_job->head_proc, new_proc);
	char *arg1[2] = {"wc", NULL};
	new_proc = creat_proc(arg1, g_shell.envl, "/usr/bin/wc");
	printf("is_builtin = %d\n", new_proc->is_builtin);
	new_job->head_proc = add_proc(new_job->head_proc, new_proc);
	char *arg2[4] = {"set", "..", "/", NULL};
	new_proc = creat_proc(arg2, g_shell.envl, "set");
	new_job->head_proc = add_proc(new_job->head_proc, new_proc);
	g_shell.head_job = add_job(g_shell.head_job, new_job);
	// NEW JOB HERE 
	new_job = NULL;
	new_proc = NULL;
	new_job = creat_job("ls -a | echo salut les gens");
	char *brg[3] = {"set", "-R", NULL};
	new_proc = creat_proc(brg, g_shell.envl, "set");
	new_job->head_proc = add_proc(new_job->head_proc, new_proc);
//	char *brg1[2] = {"wc", NULL};
//	new_proc = creat_proc(brg1, g_shell.envl, "/usr/bin/wc");
//	new_job->head_proc = add_proc(new_job->head_proc, new_proc);
//	char *brg2[3] = {"echo", "salut les gens", NULL};
//	new_proc = creat_proc(brg2, g_shell.envl, "/bin/echo");
//	printf("is_builtin = %d\n", new_proc->is_builtin);
//	new_job->head_proc = add_proc(new_job->head_proc, new_proc);
	
	printf("1icika\n");
//	g_shell.head_job = add_job(g_shell.head_job, new_job);

	printf("1ici\n");
	printf("ici\n");
	launch_job(g_shell.head_job, 1);
	printf("fin\n");
}*/

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
	//	execution(&lex);
		lexer_destroy(&lex);
	}
}
