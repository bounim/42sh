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

#include "parser.h"

// FIXME regression: >x y

static int				add_argument(t_lexer_token *n, t_lexer_token **cur)
{
	// FIXME what if !*cur
	if (n->arg_foot)
		n->arg_foot->next = *cur;
	else
		n->arg_head = *cur;
	n->arg_foot = *cur;
	n->arg_nb++;
	return (0);
}

static int				add_assignement_word(t_lexer_token *n,
		t_lexer_token **cur)
{
	// FIXME what if !*cur
	if (n->assign_foot)
		n->assign_foot->next = *cur;
	else
		n->assign_head = *cur;
	n->assign_foot = *cur;
	n->assign_nb++;
	return (0);
}

static int				add_redirection(t_lexer_token *n, t_lexer_token **cur)
{
	(*cur)->rtype = get_redirect((*cur)->buffer, (*cur)->size);
	if ((*cur)->rtype == DLESS || (*cur)->rtype == DLESSDASH)
		(*cur)->heredoc = 1; // FIXME
	*cur = (*cur)->next;
	// FIXME if !*cur then error???
	if (n->redir_foot)
		n->redir_foot->next = *cur;
	else
		n->redir_head = *cur;
	n->redir_foot = *cur;
	n->redir_nb++;
	return (0);
}

static int			parser_new_command(t_lexer_token *n, t_lexer_token **cur)
{
	int		r;

	r = 0;
	while (*cur && !is_sep_operator(*cur))
	{
		if (is_shift((*cur)->buffer, (*cur)->size))
			r = add_redirection(n, cur);
		else if ((*cur)->type == LEX_TP_IO) // FIXME what if already set
			n->next_io = ft_memtoi((*cur)->buffer, (*cur)->size);
		else if (!(*cur)->arg_next && (uint8_t *)ft_memchr((*cur)->buffer,
					'=', (*cur)->size) > (*cur)->buffer)
			r = add_assignement_word(n, cur);
		else
			r = add_argument(n, cur);
		if (r != 0)
			return (r);
		if ((*cur)->next && is_sep_operator((*cur)->next))
			break ;
		(*cur) = (*cur)->next;
	}
	return (0);
}

int					parser_new_elem(t_lexer_token **cur)
{
	if (((*cur)->ptype = get_node_type(*cur)) == PARSER_COMMAND
			|| is_shift((*cur)->buffer, (*cur)->size))
		return (parser_new_command(*cur, cur));
	return (0);
}
