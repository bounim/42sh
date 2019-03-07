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
#include "lexer.h"

enum e_parser_type	get_node_type(t_lexer_token *token)
{
	if (is_and(token->buffer, token->size) || is_or(token->buffer, token->size))
		return (PARSER_AND_OR);
	if (is_pipeline(token->buffer, token->size))
		return (PARSER_PIPE);
	if (is_shift(token->buffer, token->size))
		return (PARSER_REDIRECT);
	if (is_semicolon(token->buffer, token->size))
		return (PARSER_SEMICOLON);
	return (PARSER_COMMAND);
}

uint8_t			is_sep_operator(t_lexer_token *t)
{
	if (t && t->type == LEX_TP_OP && !is_shift(t->buffer, t->size))
		return (1);
	return (0);
}

int				add_argument(t_parser_node *n, t_lexer_token **tmp)
{
	t_word	*new;

	if (!(new = malloc(sizeof(*new))))
		return (-1);
	ft_memset(new, 0, sizeof(*new));
	if (*tmp)
	{
		if (!(new->buf = malloc(sizeof(uint8_t) * (*tmp)->size)))
			return (-1);
		ft_memcpy(new->buf, (*tmp)->buffer, (*tmp)->size);
		new->size = (*tmp)->size;
	}
	if (n->arg_head)
		n->arg_foot->next = new;
	else
		n->arg_head = new;
	n->arg_foot = new;
	n->arg_nb++;
	return (0);
}

void		print_word(t_word *r)
{
	t_word *tmp;

	tmp = r;
	while (tmp)
	{
		print_token(tmp->buf, tmp->size);
		tmp = tmp->next;
	}
}

int				add_assignement_word(t_parser_node *n, t_lexer_token **tmp)
{
	t_word	*new;

	ft_putendl("adding assign");
	if (!(new = malloc(sizeof(*new))))
		return (-1);
	ft_memset(new, 0, sizeof(*new));
	if (*tmp)
	{
		if (!(new->buf = malloc(sizeof(uint8_t) * (*tmp)->size)))
			return (-1);
		ft_memcpy(new->buf, (*tmp)->buffer, (*tmp)->size);
		new->size = (*tmp)->size;
	}
	if (n->assign_head)
		n->assign_foot->next = new;
	else
		n->assign_head = new;
	n->assign_foot = new;
	n->assign_nb++;
	return (0);
}

void		print_redir(t_redir *r)
{
	t_redir *tmp;

	tmp = r;
	while (tmp)
	{
		print_token(tmp->redir_out, tmp->redir_size);
		tmp = tmp->next;
	}
}

int				add_redirection(t_parser_node *n, t_lexer_token **tmp)
{
	t_redir		*new;

	if (!(new = malloc(sizeof(*new))))
		return (-1);
	ft_memset(new, 0, sizeof(*new));
	new->redir_type = get_redirect((*tmp)->buffer, (*tmp)->size);
	*tmp = (*tmp)->next;
	if (*tmp)
	{
		if (!(new->redir_out = malloc(sizeof(uint8_t) * (*tmp)->size)))
		{
			free(new);
			return (-1);
		}
		ft_memcpy(new->redir_out, (*tmp)->buffer, (*tmp)->size);
		new->redir_size = (*tmp)->size;
	}
	if (new->redir_type == DLESS || new->redir_type == DLESSDASH)
		new->heredoc = 1;
	if (n->redir_head)
		n->redir_foot->next = new;
	else
		n->redir_head = new;
	n->redir_foot = new;
	n->redir_nb++;
	return (0);
}

int			parser_new_command(t_parser_node *n, t_lexer_token **tmp)
{
	int		r;

	while (*tmp && !is_sep_operator(*tmp))
	{
		if (is_shift((*tmp)->buffer, (*tmp)->size))
			r = add_redirection(n, tmp);
    else if ((*tmp)->type == LEX_TP_IO)
			n->next_io = ft_memtoi((*tmp)->buffer, (*tmp)->size);
		else if (!n->arg_head && (uint8_t *)ft_memchr((*tmp)->buffer, (*tmp)->size, '=') > (*tmp)->buffer)
			r = add_assignement_word(n, tmp);
		else
		{
			ft_putendl("mdrrr");
			r = add_argument(n, tmp);
		}
		if (r != 0)
			return (r);
		(*tmp) = (*tmp)->next;		
	}
	return (0);
}

t_parser_node	*parser_new_elem(t_lexer_token **tmp)
{
	t_parser_node	*n;

	if (!(n = malloc(sizeof(*n))))
		return (NULL);
	ft_memset(n, 0, sizeof(*n));
	if ((n->type = get_node_type(*tmp)) == PARSER_COMMAND || is_shift((*tmp)->buffer, (*tmp)->size))
		parser_new_command(n, tmp);
	else
		*tmp = (*tmp)->next;
	return (n);
}
