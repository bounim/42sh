/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 16:06:31 by emartine          #+#    #+#             */
/*   Updated: 2019/03/06 15:59:46 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <stdint.h>
# include "libft.h"

enum							e_lexer_type
{
	TYPE_OPERATOR = 0,
	TYPE_WORD,
	TYPE_HEREDOC,
};

/*
** cannot_append: delimited token
*/

typedef struct s_lexer_token	t_lexer_token;

struct							s_lexer_token
{
	t_lexer_token				*previous;
	t_lexer_token				*next;
	enum e_lexer_type			type;
	size_t						line_y;
	size_t						line_x;
	uint8_t						*buffer;
	size_t						buffer_size;
	int							cannot_append;
};

typedef struct					s_heredoc
{
	int							skip_tabs; // 0 => <<, 1 => <<-
	uint8_t						*delimiter;
	size_t						delimiter_size;
	uint8_t						*buffer;
	size_t						buffer_size;
}								t_heredoc;

/* FIXME
** When lexer returns, these can be set (0 = default / unset)
** impl_error: internal error, shouldn't happen
** quoted: TODO
** heredoc: TODO
*/

# define EXPANSION_STACK_MAX 128

typedef struct					s_lexer
{
	int							init;
	t_lexer_token				*head;
	t_lexer_token				*foot;
	uint8_t						*line;
	size_t						line_size;
	size_t						line_y;
	size_t						i;
	int							impl_error;
	int							backslash_newline;
	int							quoted;
	int							next_quoted;
	uint8_t						expansion_stack[EXPANSION_STACK_MAX];
	size_t						expansion_size;
	int							next_expansion;
	t_heredoc					*heredoc_queue;
	int							heredoc;
	t_heredoc					*heredoc_ptr;
}								t_lexer;

/*
** Run lexer and parser on a line.
** Must memset to 0 before first call.
** line doesn't contain a LF.
** Returns -1 on error, 0 on success.
** When erroring, must check exit variables (quoted...) to find the
** reason, if all are 0, a malloc failed (out of memory).
** See t_lexer definition above.
*/

int								lexer_read(t_lexer *lex, uint8_t *line,
		size_t line_size);
void							lexer_destroy(t_lexer *lex);

#endif
