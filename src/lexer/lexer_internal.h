/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 18:43:21 by emartine          #+#    #+#             */
/*   Updated: 2019/03/06 15:59:46 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_INTERNAL_H
# define LEXER_INTERNAL_H

# include "twenty_one_sh.h"

enum							e_lexer_type
{
	TYPE_OPERATOR = 0,
	TYPE_WORD,
	TYPE_IO_NUMBER,
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
	int							is_number;
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
	int							input_end;
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
** Token functions
**
** Return -1 on fatal error, 0 on success, 1 if it can't match the character.
*/

int								next_quoted(t_lexer *lex);
int								line_end(t_lexer *lex);
int								unquoted_backslash_newline(t_lexer *lex);
int								heredoc(t_lexer *lex);
int								operator_append(t_lexer *lex);
int								operator_end(t_lexer *lex);
int								quoting(t_lexer *lex);
int								expansion(t_lexer *lex);
int								operator_new(t_lexer *lex);
int								unquoted_blank(t_lexer *lex);
int								word_append(t_lexer *lex);
int								comment(t_lexer *lex);
int								word_new(t_lexer *lex);

/*
** token: allocate a token node (linked list)
** append: add current byte to existing token (or at least consume it)
*/

int								token(t_lexer *lex, enum e_lexer_type);
int								append(t_lexer *lex);

#endif
