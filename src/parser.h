/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 17:46:28 by kberisha          #+#    #+#             */
/*   Updated: 2019/02/07 17:46:32 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <unistd.h>
# include "lexer/lexer_internal.h"

void							print_arg(t_lexer_token *tok);
void							print_redir(t_lexer_token *tok);
void							print_assign(t_lexer_token *tok);

uint8_t							is_sep_operator(t_lexer_token *t);
enum e_parser_type				get_node_type(t_lexer_token *token);
enum e_redirect_type			get_redirect(uint8_t *buffer, size_t size);
/*
** returns equals sign position (variable name length) or 0 if invalid
*/
size_t							is_assignment(uint8_t *buffer, size_t size);

int								parser_create_tree(t_lexer *lex);
int								parser_input_end(t_lexer *lex);
int								parser_new_elem(t_lexer *lex,
		t_lexer_token **cur);
int								parser_add_tree(t_lexer *lex, t_lexer_token *n);
void							structure(t_lexer_token *root, int level);

#endif
