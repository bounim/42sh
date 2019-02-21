/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 18:43:21 by emartine          #+#    #+#             */
/*   Updated: 2019/02/21 18:43:22 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** Token functions
**
** Return -1 on fatal error, 0 on success, 1 if it can't match the character.
*/

int		unquoted_backslash_newline(t_lexer *lex);
int		heredoc(t_lexer *lex);
int		operator_append(t_lexer *lex);
int		operator_end(t_lexer *lex);
int		quoting(t_lexer *lex);
int		expansion(t_lexer *lex);
int		operator_new(t_lexer *lex);
int		unquoted_blank(t_lexer *lex);
int		word_append(t_lexer *lex);
int		comment(t_lexer *lex);
int		word_new(t_lexer *lex);
int		line_end(t_lexer *lex);

/*
** Internal functions
** token: allocate a token node (linked list)
** append: add current byte to existing token
** parser: load parser TODO
*/

// FIXME enum
int		token(t_lexer *lex, enum e_lexer_type);
int		append(t_lexer *lex, enum e_lexer_type type);
int		parser(t_lexer *lex);
