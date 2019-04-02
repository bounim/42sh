/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_printer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 01:30:55 by kberisha          #+#    #+#             */
/*   Updated: 2019/02/18 01:30:57 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"
#include "parser.h"
#include "expansions.h"

void		print_arg(t_lexer_token *tok)
{
	t_lexer_token	*cur;

	cur = tok->arg_head;
	if (!cur)
		printer_str(&g_shell.out, "NULL");
	while (cur)
	{
		printer_bin(&g_shell.out, cur->buffer, cur->size);
		printer_char(&g_shell.out, ' ');
		cur = cur->arg_next;
	}
	printer_endl(&g_shell.out);
	printer_flush(&g_shell.out);
}

void		print_redir(t_lexer_token *tok)
{
	t_lexer_token	*cur;

	cur = tok->redir_head;
	if (!cur)
		printer_str(&g_shell.out, "NULL");
	while (cur)
	{
		printer_bin(&g_shell.out, cur->buffer, cur->size);
		printer_char(&g_shell.out, ' ');
		cur = cur->redir_next;
	}
	printer_endl(&g_shell.out);
	printer_flush(&g_shell.out);
}

void		print_assign(t_lexer_token *tok)
{
	t_lexer_token	*cur;

	cur = tok->assign_head;
	if (!cur)
		printer_str(&g_shell.out, "NULL");
	while (cur)
	{
		printer_bin(&g_shell.out, cur->buffer, cur->size);
		printer_char(&g_shell.out, ' ');
		cur = cur->assign_next;
	}
	printer_endl(&g_shell.out);
	printer_flush(&g_shell.out);
}

static void	padding(size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		printer_char(&g_shell.out, '\t');
		i++;
	}
}

void		structure(t_lexer_token *root, int level)
{
	if (level > 10)
		return ;
	if (!root)
	{
		padding(level);
		printer_char(&g_shell.out, '~');
		printer_endl(&g_shell.out);
	}
	else
	{
		structure(root->right, level + 1);
		padding(level);
		if (root->ptype != PARSER_COMMAND)
			printer_bin(&g_shell.out, root->buffer, root->size);
		else if (root->arg_head)
			printer_bin(&g_shell.out, root->arg_head->buffer,
					root->arg_head->size);
		else
			printer_char(&g_shell.out, '?');
		printer_endl(&g_shell.out);
		structure(root->left, level + 1);
	}
	printer_flush(&g_shell.out);
}
