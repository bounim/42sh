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

# include <stdio.h> //a enleverrrr
# include <stdlib.h>
# include <unistd.h>
# include "lexer/lexer_internal.h"

/*typedef struct s_word			t_word;

struct							s_word
{
	t_buffer					*buffer; //changer le nom TODO statically allocate
	uint8_t						tilded;
	t_word						*next;
};

typedef struct s_parser_node	t_parser_node;

struct							s_parser_node
{
	t_lexer_token				*token;
	uint8_t						*buffer;
	size_t						size;
	t_redir						*redir_head;
	t_redir						*redir_foot;
	size_t						redir_nb;
	t_word						*assign_head;
	t_word						*assign_foot;
	size_t						assign_nb;
	t_word						*arg_head;
	t_word						*arg_foot;
	size_t						arg_nb;
	int							next_io;
	enum e_parser_type			type;
	t_parser_node				*left;
	t_parser_node				*right;
	t_parser_node				*listNext;
};

typedef struct s_parser			t_parser;

struct							s_parser
{
	t_parser_node				*head;
	t_parser_node				*nodeList;
};*/

// TODO:

/*void							structure(t_parser_node *root, int level);
void							parser_print(t_parser_node *tree);
void							print_redir(t_redir *r);
void							print_word(t_word *r);*/

void							print_arg(t_lexer_token *tok);
void							print_redir(t_lexer_token *tok);
void							print_assign(t_lexer_token *tok);

/*void							do_expansions(t_parser_node *tree);

void							parser_init(t_parser *parser);*/

uint8_t							is_or(uint8_t *buffer, size_t buffer_size);
uint8_t							is_and(uint8_t *buffer, size_t buffer_size);
uint8_t							is_pipeline(uint8_t *buffer,
		size_t buffer_size);
uint8_t							is_semicolon(uint8_t *buffer,
		size_t buffer_size);
uint8_t							is_shift(uint8_t *buffer, size_t buffer_size);
uint8_t							is_quote(uint8_t c);
uint8_t							is_sep_operator(t_lexer_token *t);
enum e_parser_type				get_node_type(t_lexer_token *token);

enum e_redirect_type			get_redirect(uint8_t *buffer, size_t size);


// XXX DONE:

int								parser_create_tree(t_lexer *lex);
int								parser_new_elem(t_lexer_token **cur);
int								parser_add_tree(t_lexer *lex, t_lexer_token *n);
void							parser_destroy(t_lexer *lex);
void							structure(t_lexer_token *root, int level);

#endif
