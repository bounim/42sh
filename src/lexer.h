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

enum				e_lexer_token
{
	LEX_WORD = 0,
	LEX_ASSIGNMENT_WORD,
	LEX_NAME,
	LEX_NEWLINE,
	LEX_IO_NUMBER,
	LEX_OP_AND_IF,
	LEX_OP_OR_IF,
	LEX_OP_DSEMI,
	LEX_OP_DLESS,
	LEX_OP_DGREAT,
	LEX_OP_LESSAND,
	LEX_OP_GREATAND,
	LEX_OP_LESSGREAT,
	LEX_OP_DLESSDASH,
	LEX_OP_CLOBBER,
	LEX_RES_IF,
	LEX_RES_THEN,
	LEX_RES_ELSE,
	LEX_RES_ELIF,
	LEX_RES_FI,
	LEX_RES_DO,
	LEX_RES_DONE,
	LEX_RES_CASE,
	LEX_RES_ESAC,
	LEX_RES_WHILE,
	LEX_RES_UNTIL,
	LEX_RES_FOR,
	LEX_REC_LBRACE,
	LEX_REC_RBRACE,
	LEX_REC_BANG,
	LEX_REC_IN,
	LEX_OP_PIPE,
	LEX_OP_LPAREN,
	LEX_OP_RPAREN,
	LEX_OP_LESS,
	LEX_OP_GREAT,
	LEX_OP_AMP,
	LEX_OP_SEMI,
};

typedef struct s_lexer_token	t_lexer_token;

struct							s_lexer_token
{
	enum e_lexer_token			token;
	size_t						buffer_position;
	size_t						in_buffer;
	t_lexer_token				*previous;
	t_lexer_token				*next;
	char						*string;
	size_t						string_length;
	int64_t						number;
};

/*
** When lexer exits, these can be set (0 = default / unset)
** nomatch: cannot match a token
** quote: 1 - quote not closed, 2 - dquote not closed
*/

typedef struct					s_lexer
{
	t_lexer_token				*head;
	t_lexer_token				*foot;
	char						*buffer;
	size_t						buffer_length;
	size_t						i;
	int							nomatch;
	int							quote;
}								t_lexer;

void							lexer_init(t_lexer *lex, char *buffer,
		size_t buffer_length);
/*
** Returns -1 on error, 0 on success.
** When erroring, must check exit variables (nomatch, quote...) to find the
** reason, if all are 0, a malloc failed (out of memory).
** See t_lexer definition above.
*/
int								lexer_read(t_lexer *lex);
void							lexer_destroy(t_lexer *lex);

/*
** Token functions
**
** Return -1 on fatal error, 0 on success, 1 if it can't match a token.
*/

int								lexer_quote(t_lexer *lex);
int								lexer_number(t_lexer *lex);
int								lexer_newline(t_lexer *lex);

/*
** Internal functions
** token: allocate a token node (linked list)
** keyword: check if next word is a keyword (not quoted, may have backslahes)
*/

t_lexer_token					*lexer_token(t_lexer *lex,
		enum e_lexer_token token);
size_t							lexer_keyword(t_lexer *lex, char *keyword);

#endif
