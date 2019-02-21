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
	TYPE_FOO = 0,
};

typedef struct s_lexer_token	t_lexer_token;

struct							s_lexer_token
{
	t_lexer_token				*previous;
	t_lexer_token				*next;
	enum e_lexer_type			type;
	size_t						line_y; // TODO
	size_t						line_x;
	uint8_t						*buffer;
	size_t						size;
};

typedef struct					s_heredoc
{
	int							skip_tabs; // 0 => <<, 1 => <<-
	uint8_t						*delimiter;
	size_t						delimiter_size;
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
}								t_lexer;

/*
** check that an input buffer can be used in the lexer
** assumes that this function has been called after each line return
*/

//uint8_t							lexer_check_line(uint8_t *buffer, size_t size);

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
