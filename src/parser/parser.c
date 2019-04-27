/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 18:10:56 by kberisha          #+#    #+#             */
/*   Updated: 2019/02/28 05:11:03 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"
#include "parser.h"

static void		parser_error(t_lexer_token *tok)
{
	g_shell.exit_code = 258;
	printer_str(&g_shell.err, g_shell.progname);
	printer_str(&g_shell.err, ": syntax error near unexpected token `");
	printer_bin(&g_shell.err, tok->buffer, tok->size);
	printer_str(&g_shell.err, "' on line ");
	printer_ulong(&g_shell.err, tok->line_y + 1);
	printer_char(&g_shell.err, ':');
	printer_ulong(&g_shell.err, tok->line_x + 1);
	printer_endl(&g_shell.err);
	printer_flush(&g_shell.err);
}

static void		parser_debug(t_lexer_token *n)
{
	if (g_shell.debug_mode)
	{
		ft_putendl("args");
		print_arg(n);
		ft_putendl("redirs");
		print_redir(n);
		ft_putendl("assignement words");
		print_assign(n);
		ft_putendl("END.");
	}
}

int				parser_create_tree(t_lexer *lex)
{
	t_lexer_token	*cur;
	t_lexer_token	*n;

	cur = lex->last_parsed ? lex->last_parsed->next : lex->head;
	while (cur)
	{
		n = cur;
		if (parser_new_elem(lex, &cur) < 0 || parser_add_tree(lex, n) < 0)
		{
			parser_error(n);
			return (-1);
		}
		lex->last_parsed = n;
		parser_debug(n);
	}
	if (g_shell.debug_mode)
		structure(lex->root, 0);
	return (0);
}

int				parser_input_end(t_lexer *lex)
{
	return (lex->last_parsed && (lex->last_parsed->ptype == PARSER_COMMAND
				|| lex->last_parsed->ptype == PARSER_SEPARATOR));
}
