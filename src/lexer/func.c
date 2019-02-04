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

#include <stdio.h> // XXX

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

static int	is_digit(uint8_t c)
{
	return (c >= '0' && c <= '9');
}

int			lexer_operator(t_lexer *lex)
{
	int	r;

	if (is_op(lex->buffer[lex->i]) && !lex->quote)
	{
	puts("lexer operator");
		if (lex->state == LEX_ST_GEN || lex->state == LEX_ST_BLK
				|| lex->state == LEX_ST_WD)
			r = lexer_token(lex, LEX_TP_OP);
		else if (lex->state == LEX_ST_NB || lex->state == LEX_ST_OP)
			r = lexer_append(lex, LEX_TP_OP);
		else
			return (1);
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
	printf("lex quote = %d\n", lex->quote);
		if (lex->buffer[lex->i] == '\\')
		{
			lex->bgstate = lex->state;
			lex->state = LEX_ST_BS;
		}
		else
		{
			if (lex->state == LEX_ST_BLK || lex->state == LEX_ST_GEN)
				lex->startqu = 1;
			lex->state = LEX_ST_QU;
			lex->quotetype = lex->buffer[lex->i]; // FIXME
		}
		lex->quote = 1;
		return (0);
	}
	return (1);
}

int			lexer_inquote(t_lexer *lex)
{
	if (lex->state == LEX_ST_QU)
	{
	puts("lexer_inquote");
		if (lex->buffer[lex->i] == lex->quotetype)
		{
			lex->state = LEX_ST_WD;
			lex->quote = 1;
			lex->quotetype = 0;
		}
		else
		{
			if (lex->buffer[lex->i] == '\\' && lex->quotetype == '\"')
			{
				lex->state = LEX_ST_BS;
				lex->bgstate = LEX_ST_QU;
			}
			else
			{
				lex->state = LEX_ST_QU;
				if (lex->startqu)
				{
					lex->startqu = 0;
					return (lexer_token(lex, LEX_TP_WD));
				}
				return (lexer_append(lex, LEX_TP_WD));
			}
		}
		return (0); //a mettre ici ?....
	}
	return (1);
}

int		lexer_backslash(t_lexer *lex)
{
	if (lex->state == LEX_ST_BS)
	{
		lex->quote = 0;
		if (lex->bgstate == LEX_ST_QU)
		{
			puts("lexer_bs");
			lex->state = LEX_ST_QU;
			lex->bgstate = LEX_ST_GEN; //pas oblige je crois
			if (lex->intoken)
				return (lexer_append(lex, LEX_TP_WD)); //voir le cas ou "\", le token n'existe pas encore....
			return (lexer_token(lex, LEX_TP_WD));
		}
		else if (lex->bgstate == LEX_ST_BLK || lex->bgstate == LEX_ST_GEN || lex->bgstate == LEX_ST_OP)
		{
			lex->state = LEX_ST_WD;
			return (lexer_token(lex, LEX_TP_WD));
		}
		else
		{
			if (is_digit(lex->buffer[lex->i]) && lex->bgstate == LEX_ST_NB)
				lex->state = LEX_ST_NB;
			else
				lex->state = LEX_ST_WD;
			return (lexer_append(lex, LEX_TP_WD));
		}
	}
	return (1);
}

int			lexer_blank(t_lexer *lex)
{
	if (is_blank(lex->buffer[lex->i]) && !lex->quote)
	{
	puts("lexer_blk");
		lex->state = LEX_ST_BLK;
		lex->intoken = 0;
		return (0);
	}
	return (1);
}

int			lexer_word(t_lexer *lex)
{
	if (lex->state == LEX_ST_GEN || lex->state == LEX_ST_BLK)
	{
	puts("lexer_word");
		if (is_digit(lex->buffer[lex->i]))
			lex->state = LEX_ST_NB;
		else
			lex->state = LEX_ST_WD;
		return (lexer_token(lex, LEX_TP_WD));
	}
	else if (lex->state == LEX_ST_WD || lex->state == LEX_ST_NB)
	{
		if (is_digit(lex->buffer[lex->i]) && lex->state == LEX_ST_NB)
			lex->state = LEX_ST_NB;
		else
			lex->state = LEX_ST_WD;
		return (lexer_append(lex, LEX_TP_WD));
	}
	return (1);
}
