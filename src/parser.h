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
#define PARSER_H

#include <stdio.h> //a enleverrrr
#include <stdlib.h>
#include <unistd.h>
#include "lexer.h"

enum				e_parser_type
{
	PARSER_COMMAND = -1,
	PARSER_HEREDOC,
	PARSER_REDIRECT,
	PARSER_PIPE,
	PARSER_AND_OR,
	PARSER_SEMICOLON
};

typedef struct s_parser_node	t_parser_node;

struct							s_parser_node
{
	t_lexer_token				*token;
	uint8_t						*buffer;
	size_t						buffer_length;
	t_redir						*io_redir;
	// uint8_t						**args;
	size_t						*args_size;
	size_t						args_nb;
	enum e_parser_type			type;
	t_parser_node		*left;
	t_parser_node		*right;
};

typedef struct s_parser			t_parser;

struct 							s_parser
{
	t_parser_node	*head;
	t_parser_node	*foot;
	// size_t		nb_op;
	// size_t		nb_wd;
};

void			structure(t_parser_node *root, int level);
void			parser_print(t_parser_node *tree);
void			print_token(uint8_t *buffer, size_t size);

void			parser_init(t_parser *parser);
int				parser_create_tree(t_lexer *lexer);
t_parser_node	*parser_new_elem(t_lexer_token *n);
void			parser_add_tree(t_parser_node **head, t_parser_node *n);

uint8_t		is_or(uint8_t *buffer, size_t buffer_size);
uint8_t		is_and(uint8_t *buffer, size_t buffer_size);
uint8_t		is_pipeline(uint8_t *buffer, size_t buffer_size);
uint8_t		is_semicolon(uint8_t *buffer, size_t buffer_size);
uint8_t		is_shift(uint8_t *buffer, size_t buffer_size);

#endif
