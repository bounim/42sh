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

#include "parser.h"
#include "lexer.h"

void						parser_init(t_parser *parser)
{
	ft_memset(parser, 0, sizeof(*parser));
	parser->head = NULL;
}

void						parser_create_args(t_lexer_token **head)
{
	t_lexer_token	*cur;
	t_lexer_token	*prev;

	cur = (*head)->next;
	while (cur && cur->type == LEX_TP_WD)
	{
		if (!((*head)->args[(*head)->args_nb] = malloc(cur->size * sizeof(uint8_t))))
			return ;
		ft_memcpy((*head)->args[(*head)->args_nb], cur->buffer, cur->size);
		(*head)->args_size[(*head)->args_nb] = cur->size;
		(*head)->args_nb++;
		prev = cur;
		cur = cur->next;
		lexer_free_token(&prev);
	}
	if (cur && cur->type != LEX_TP_WD)
		(*head)->next = cur;
	else
		(*head)->next = NULL;
}

/*	gets redirection type
**	logique
*/

enum	e_redirect_type		get_redirect(uint8_t *buffer, size_t size)
{
	if (size == 2)
	{
		if (!ft_memcmp(">>", (const uint8_t*)buffer, size))
			return (DGREAT);
		if (!ft_memcmp("<<", (const uint8_t*)buffer, size))
			return (DLESS);
		if (!ft_memcmp(">&", (const uint8_t*)buffer, size))
			return (GREATAND);
		if (!ft_memcmp("<&", (const uint8_t*)buffer, size))
			return (LESSAND);
		if (!ft_memcmp("<>", (const uint8_t*)buffer, size))
			return (LESSGREAT);
	}
	else if (size == 1)
	{
		if (!ft_memcmp(">", (const uint8_t*)buffer, size))
			return (GREAT);
		if (!ft_memcmp("<", (const uint8_t*)buffer, size))
			return (LESS);
	}
	return (0);
}

void							tokenstr(char *str, t_lexer_token *tok)
{
	ft_putendl(str);
	print_token(tok->buffer, tok->size);
}

int								parser_create_tree(t_parser *parser, t_lexer *lexer)
{
	// t_parser		*parser;
	t_lexer_token	*tmp;
	t_parser_node	*n;

	n = NULL;
	if (!(parser = malloc(sizeof(*parser))))
		return (-1);
	parser_init(parser);
	lexer_print(&lexer->head);
	tmp = lexer->head;
	while (tmp)
	{
		if (!(n = parser_new_elem(&tmp)))
			return (-1);
		parser_add_tree(&parser->head, n);
    ft_putendl("args");
		print_word(n->arg_head);
		ft_putendl("END.");
		ft_putendl("redirs");
		print_redir(n->redir_head);
		ft_putendl("END.");
		ft_putendl("assignement words");
		print_word(n->assign_head);
		ft_putendl("END.");
		if (tmp)
			tmp = tmp->next;
	}
	structure(parser->head, 0);
	return (0);
}
