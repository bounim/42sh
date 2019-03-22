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

/*	gets redirection type
**	logique
*/

enum e_redirect_type	get_redirect(uint8_t *buffer, size_t size)
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
	// FIXME else internal error?
	return (0);
}

int						parser_create_tree(t_lexer *lex)
{
	t_lexer_token	*cur;
	t_lexer_token	*n;

	cur = lex->head;
	while (cur)
	{
		n = cur;
		if (parser_new_elem(&cur) < 0 || parser_add_tree(lex, n) < 0)
			return (-1);
		ft_putendl("args");
		print_arg(n);
		ft_putendl("END.");
		ft_putendl("redirs");
		print_redir(n);
		ft_putendl("END.");
		ft_putendl("assignement words");
		print_assign(n);
		ft_putendl("END.");
		if (cur)
			cur = cur->next;
	}
	structure(lex->root, 0);
	//do_expansions(lex);
	return (0);
}
