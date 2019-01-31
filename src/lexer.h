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

enum							e_lexer_state
{
	LEX_ST_GEN = 0,
	LEX_ST_OP,
	LEX_ST_QU,
	LEX_ST_WD,
	LEX_ST_BLK,
	LEX_ST_BS,
	LEX_ST_DLR,
	LEX_ST_NB,
};

// TODO enum e_lexer_type

typedef struct s_lexer_token	t_lexer_token;

struct							s_lexer_token
{
	enum e_lexer_state			state; // FIXME enum e_lexer_type type
	size_t						buffer_position;
	size_t						in_buffer;
	t_lexer_token				*previous;
	t_lexer_token				*next;
};

/*
** When lexer exits, these can be set (0 = default / unset)
** nomatch: cannot match a token
** quote: 1 - quote not closed, 2 - dquote not closed
*/

typedef struct					s_lexer
{
	enum e_lexer_state			state;
	t_lexer_token				*head;
	t_lexer_token				*foot;
	uint8_t						*buffer;
	size_t						buffer_length;
	size_t						i;
	int							nomatch;
	int							quote;
}								t_lexer;

void							lexer_init(t_lexer *lex, uint8_t *buffer,
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

int								lexer_operator(t_lexer *lex);

/*
** Internal functions
** token: allocate a token node (linked list)
*/

t_lexer_token					*lexer_token(t_lexer *lex);

#endif
