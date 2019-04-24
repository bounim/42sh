/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 01:32:18 by kberisha          #+#    #+#             */
/*   Updated: 2019/02/28 04:47:50 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"
#include "parser.h"

static int		add_wd(t_lexer_token *n, t_lexer_token **cur)
{
	if (n->arg_nb == 0
			&& ((*cur)->assign_position = is_assignment((*cur)->buffer,
					(*cur)->size)) > 0)
	{
		if (n->assign_foot)
			n->assign_foot->assign_next = *cur;
		else
			n->assign_head = *cur;
		n->assign_foot = *cur;
		n->assign_nb++;
	}
	else
	{
		if (n->arg_foot)
			n->arg_foot->arg_next = *cur;
		else
			n->arg_head = *cur;
		n->arg_foot = *cur;
		n->arg_nb++;
	}
	*cur = (*cur)->next;
	return (0);
}

/*
** TODO when heredoc delimiter is quoted, needs quote removal + act differently
*/

static int		add_op(t_lexer *lex, t_lexer_token *n, t_lexer_token **cur)
{
	if ((*cur)->next == NULL || (*cur)->next->type != LEX_TP_WD)
		return (-1);
	(*cur)->rtype = get_redirect((*cur)->buffer, (*cur)->size);
	if ((*cur)->rtype == DLESS || (*cur)->rtype == DLESSDASH)
	{
		(*cur)->next->heredoc_delimiter = 1;
		if (lex->heredoc_foot)
			lex->heredoc_foot->heredoc_next = *cur;
		else
			lex->heredoc_head = *cur;
		lex->heredoc_foot = *cur;
		lex->heredoc_nb++;
	}
	(*cur)->redir_target = (*cur)->next;
	if (n->redir_foot)
		n->redir_foot->redir_next = *cur;
	else
		n->redir_head = *cur;
	(*cur)->redir_previous = n->redir_foot;
	n->redir_foot = *cur;
	n->redir_nb++;
	*cur = (*cur)->next->next;
	return (0);
}

static int		add_io(t_lexer *lex, t_lexer_token *n, t_lexer_token **cur)
{
	if ((*cur)->next == NULL)
		return (-1);
	(*cur)->next->redir_input = ft_memtoi((*cur)->buffer, (*cur)->size);
	*cur = (*cur)->next;
	return (add_op(lex, n, cur));
}

static int		parser_new_command(t_lexer *lex, t_lexer_token *n,
		t_lexer_token **cur)
{
	int	r;

	r = 0;
	while (r == 0 && *cur && !is_sep_operator(*cur))
	{
		if ((*cur)->type == LEX_TP_WD)
			r = add_wd(n, cur);
		else if ((*cur)->type == LEX_TP_IO)
			r = add_io(lex, n, cur);
		else
			r = add_op(lex, n, cur);
	}
	return (r);
}

int				parser_new_elem(t_lexer *lex, t_lexer_token **cur)
{
	(*cur)->ptype = get_node_type(*cur);
	if ((*cur)->ptype == PARSER_COMMAND)
		return (parser_new_command(lex, *cur, cur));
	if (!lex->root)
		return (-1);
	*cur = (*cur)->next;
	return (0);
}
