/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 18:23:38 by emartine          #+#    #+#             */
/*   Updated: 2019/02/01 18:23:40 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	is_blank(uint8_t c)
{
	return (c == ' ' || c == '\t');
}

static int	is_quote(uint8_t c)
{
	return (c == '\\' || c == '\'' || c == '\"');
}

static int	is_op(uint8_t c)
{
	return (c == '&' || c == '|' || c == ';' || c == '>' || c == '<');
}

int			lexer_operator(t_lexer *lex)
{
	int	r;

	if (is_op(lex->buffer[lex->i]) && !lex->quote)
	{
		if (lex->state == LEX_ST_GEN || lex->state == LEX_ST_BLK)
			r = lexer_token(lex, LEX_TP_OP);
		else if (lex->state == LEX_ST_NB || lex->state == LEX_ST_OP)
			r = lexer_append(lex, LEX_TP_OP);
		else
			r = -1; // FIXME
		lex->state = LEX_ST_OP;
		return (r);
	}
	else if (!is_op(lex->buffer[lex->i]) && !lex->quote
			&& lex->state == LEX_ST_OP)
	{
		if (!is_blank(lex->buffer[lex->i]))
		{
			lex->state = LEX_ST_WD;
			return (lexer_token(lex, LEX_TP_WD));
		}
		else
			lex->state = LEX_ST_BLK;
	}
	return (1);
}

int			lexer_quote(t_lexer *lex)
{
	if (is_quote(lex->buffer[lex->i]) && !lex->quote)
	{
		if (lex->buffer[lex->i] == '\\')
			lex->state = LEX_ST_BS;
		else
			lex->state = LEX_ST_QU;
		lex->quote = lex->buffer[lex->i]; // FIXME
		return (0);
	}
	else if (lex->state == LEX_ST_QU)
	{
		if (lex->buffer[lex->i] == lex->quote)
		{
			/*if (lex->buffer[lex->i]*/
			lex->state = LEX_ST_WD;
		}
		else
		{
			/*if (lex->buffer[lex->i] == '\\' && lex->quote == '\"')
				lex->state = LEX_ST_BS;
			else       //gerer le conflit de states qd on a un \ dans une dquote
				lex->state = LEX_ST_QU;*/
		}
	}
	return (1);
}

int			lexer_blank(t_lexer *lex)
{
	if (is_blank(lex->buffer[lex->i]) && !lex->quote)
	{
		lex->state = LEX_ST_BLK;
		return (0);
	}
	return (1);
}

int			lexer_word(t_lexer *lex)
{
	if (lex->state == LEX_ST_GEN || lex->state == LEX_ST_BLK)
	{
		//
		return (0);
	}
	return (1);
}
