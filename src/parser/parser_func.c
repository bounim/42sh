/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 01:28:43 by kberisha          #+#    #+#             */
/*   Updated: 2019/02/18 01:28:44 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"
#include "parser.h"

static int	add_root(t_lexer *lex, t_lexer_token *new)
{
	new->left = lex->root;
	lex->root->parent = new;
	lex->root = new;
	return (0);
}

static void	replace_node(t_lexer *lex, t_lexer_token *cur, t_lexer_token *new)
{
	new->left = cur;
	if (!cur->parent)
		add_root(lex, new);
	else
	{
		if (cur->parent->left == cur)
			cur->parent->left = new;
		else
			cur->parent->right = new;
		new->parent = cur->parent;
		cur->parent = new;
	}
}

static int	root_operator(t_lexer *lex, t_lexer_token *new)
{
	t_lexer_token	*cur;

	cur = lex->root;
	while (1)
	{
		if (new->ptype > cur->ptype)
		{
			if (!cur->right && (cur->ptype == PARSER_PIPE
						|| cur->ptype == PARSER_AND_OR))
				return (-1);
			replace_node(lex, cur, new);
			break ;
		}
		if (!cur->right)
		{
			if (new->ptype != PARSER_COMMAND)
				return (-1);
			cur->right = new;
			new->parent = cur;
			break ;
		}
		cur = cur->right;
	}
	return (0);
}

int			parser_add_tree(t_lexer *lex, t_lexer_token *new)
{
	if (!lex->root)
	{
		if (new->ptype != PARSER_COMMAND)
			return (-1);
		lex->root = new;
		return (0);
	}
	if (lex->root->ptype == PARSER_COMMAND)
	{
		if (new->ptype == PARSER_COMMAND)
			return (-1);
		return (add_root(lex, new));
	}
	return (root_operator(lex, new));
}
