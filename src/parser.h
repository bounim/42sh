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
	PAR_TP_WD = 0,
	PAR_TP_OP,
};

typedef struct s_parser_node	t_parser_node;

struct							s_parser_node
{
	uint8_t						*buffer;
	size_t						buffer_length;
	enum e_parser_type			cmd_type;
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

void	parser_init(t_parser *parser);
int		parser_node(t_parser *parser, uint8_t *buf, size_t size, enum e_lexer_type type);

#endif
