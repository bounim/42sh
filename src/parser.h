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
	enum e_parser_type			type;
	t_parser_node		left;
	t_parser_node		right;
}

typedef struct		s_parser
{
	t_parser_node	*head;
	// size_t		nb_op;
	// size_t		nb_wd;
}					t_parser;
