/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 16:06:31 by emartine          #+#    #+#             */
/*   Updated: 2018/10/23 16:06:33 by emartine         ###   ########.fr       */
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

typedef struct					s_wordchr
{
	/*uint8_t						b[6];
	size_t						s;*/
	uint8_t						ch;
	int							quoted;
}								t_wordchr;

/*
** cannot_append: delimited token
*/

typedef struct s_lexer_token	t_lexer_token;

struct							s_lexer_token
{
	t_lexer_token				*previous;
	t_lexer_token				*next;
	enum e_lexer_type			type;
	size_t						line_y; // TODO
	size_t						line_x;
	t_wordchr					*word;
	size_t						word_size;
	uint8_t						*operator;
	size_t						operator_size;
	int							cannot_append;
};

typedef struct					s_heredoc
{
	int							skip_tabs; // 0 => <<, 1 => <<-
	uint8_t						*delimiter;
	size_t						delimiter_size;
	uint8_t						*buffer;
	size_t						size;
	size_t						i;
}								t_heredoc;

/* FIXME
** When lexer returns, these can be set (0 = default / unset)
** impl_error: internal error, shouldn't happen
** quoted: TODO
** heredoc: TODO
*/

typedef struct					s_lexer
{
	t_lexer_token				*head;
	t_lexer_token				*foot;
	uint8_t						*line;
	size_t						line_size;
	size_t						line_y;
	size_t						i;
	int							impl_error;
	int							quoted;
	t_heredoc					*heredoc_queue;
	int							heredoc;
	t_heredoc					*heredoc_ptr;
}								t_lexer;

void							lexer_init(t_lexer *lex, uint8_t *line,
		size_t line_size);
void							lexer_newline(t_lexer *lex, uint8_t *line,
		size_t line_size);

/*
** Returns -1 on error, 0 on success.
** When erroring, must check exit variables (nomatch, quote...) to find the
** reason, if all are 0, a malloc failed (out of memory).
** See t_lexer definition above.
*/

int								lexer_read(t_lexer *lex);
void							lexer_destroy(t_lexer *lex);

#endif
