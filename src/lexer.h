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

#include <stdio.h> //BELLEK

# define SEMICOLON			";"
# define PIPE				"|"
# define LOGICAL_AND		"&&"
# define LOGICAL_OR			"||"
# define AND				"&"
# define OR					"|"
# define LESS				"<"
# define GREAT				">"
# define DLESS				"<<"
# define DGREAT				">>"

enum							e_lexer_state
{
	LEX_ST_GEN = 0,
	LEX_ST_OP,
	LEX_ST_QU,
	LEX_ST_WD,
	LEX_ST_BLK,
	LEX_ST_BS,
	LEX_ST_NB,
};

enum							e_lexer_type
{
	LEX_TP_WD = 0,
	LEX_TP_OP,
	LEX_TP_IO
};

typedef struct s_lexer_token	t_lexer_token;

struct							s_lexer_token
{
	enum e_lexer_type			type;
	size_t						buffer_position;
	uint8_t						*buffer;
	size_t						size;
	t_lexer_token				*previous;
	t_lexer_token				*next;
};

/*
** quote: quote type + quote type if != '\0'
** When lexer exits, these can be set (0 = default / unset)
** nomatch: cannot match a token
** bgstate: background state for dealing with state conflicts
** intoken: currently building a token
*/

typedef struct					s_lexer
{
	enum e_lexer_state			state;
	enum e_lexer_state			bgstate;
	t_lexer_token				*head;
	t_lexer_token				*foot;
	uint8_t						*buffer;
	size_t						buffer_length;
	size_t						i;
	int							nomatch;
	char						quote;
	char						quotetype;
	char						startqu;
	char						intoken;
}								t_lexer;

/*
** check that an input buffer can be used in the lexer
** assumes that this function has been called after each line return
*/

uint8_t		lexer_check_line(uint8_t *buffer, size_t size);

void		lexer_print_error(t_lexer *lex);

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
int								lexer_quote(t_lexer *lex);
int								lexer_inquote(t_lexer *lex);
int								lexer_backslash(t_lexer *lex);
int								lexer_word(t_lexer *lex);
int								lexer_blank(t_lexer *lex);

/*
** Internal functions
** token: allocate a token node (linked list)
*/

int								lexer_token(t_lexer *lex, enum e_lexer_type);
int								lexer_append(t_lexer *lex,
		enum e_lexer_type type);

#endif
