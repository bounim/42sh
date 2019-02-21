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


/* pas a la norme je sais mais jsais pas comment faire autrement pour l'instant
** returns 1 if the tested buffer is a valid operator, 0 if not
*/

static int	op_list(uint8_t *buf, size_t size)
{
	char	*tab[] = {";", "|", "&", "||", "&&", "<&", ">&", "<>", "<", "<<", ">", ">>"}; //on laisse de cote le cas du >&-
	size_t	i;

	i = 0;
	while (i < 12)
	{
		if (size == ft_strlen(tab[i]) && !ft_memcmp(buf, tab[i], size))
			return (1);
		i++;
	}
	return (0);
}

static int	is_digit(uint8_t c)
{
	return (c >= '0' && c <= '9');
}

uint8_t		lexer_check_line(uint8_t *buffer, size_t size)
{
	size_t		i;
	uint8_t		c;

	i = 0;
	c = 0;
	while (i < size)
	{
		if (buffer[i] == '\\')
		{
			if (i == size - 1 && c == 0)
				return (buffer[i]);
			if (i == size - 1 && c != '\"')
				return (c);
		}
		else if (buffer[i] == '\'')
			c = (c == '\'') ? 0 : buffer[i];
		else if (buffer[i] == '\"' && c == '\"' && buffer[i - 1] != '\\')
			c = 0;
		else if (buffer[i] == '\"' && c == 0)
			c = buffer[i];
		i++;
	}
	return (c);
}

/* checks in the "valid operators' list" and returns 1 if the token to be created
** is not in the list, meaning a new operator token must be created, and 0 if success
*/

int			lexer_check_op(t_lexer *lex)
{
	uint8_t	*tmp;

	if (!(tmp = malloc(lex->foot->size + 1)))
		return (-1);
	ft_memcpy(tmp, lex->foot->buffer, lex->foot->size);
	tmp[lex->foot->size] = lex->buffer[lex->i];
	printf("tmp = %s\n", tmp);
	if (op_list(tmp, lex->foot->size + 1))
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}

int			lexer_operator(t_lexer *lex)
{
	int	r;

	if (is_op(lex->buffer[lex->i]) && !lex->quote)
	{
		puts("lexer operator");
		if (lex->state == LEX_ST_GEN || lex->state == LEX_ST_BLK
				|| lex->state == LEX_ST_WD || (lex->state == LEX_ST_NB
					&& lex->buffer[lex->i] != '>' && lex->buffer[lex->i] != '<'))
			r = lexer_token(lex, LEX_TP_OP);
		else if (lex->state == LEX_ST_NB)
		{
			lex->foot->type = LEX_TP_IO;
			r = lexer_token(lex, LEX_TP_OP);
		}
		else if (lex->state == LEX_ST_OP)
		{
			if (lexer_check_op(lex))
				r = lexer_token(lex, LEX_TP_OP);
			else
				r = lexer_append(lex, LEX_TP_OP); //ici
		}
		else
			return (1);  //c pas cense etre return (0) ? :/
		lex->state = LEX_ST_OP;
		return (r);
	}
	return (1);
}

int		lexer_end_operator(t_lexer *lex)
{
	if (!is_op(lex->buffer[lex->i]) && !lex->quote
			&& lex->state == LEX_ST_OP && !is_quote(lex->buffer[lex->i]))
	{
		if (lex->buffer[lex->i] == '-' && lex->foot->buffer[lex->foot->size - 1] == '&')
		{
			lex->state = LEX_ST_OP;					//attention a ne pas avoir de bails genre >&-& mdrr //ici
			return (lexer_append(lex, LEX_TP_OP));
		}
		else if (!is_blank(lex->buffer[lex->i]))
		{
			lex->state = LEX_ST_WD;
			return (lexer_token(lex, LEX_TP_WD));
		}
		else
			lex->state = LEX_ST_BLK; //et la faut pas rajouter un return qqchose ?
	}
	return (1);
}

int			lexer_quote(t_lexer *lex)
{
	if (is_quote(lex->buffer[lex->i]) && !lex->quote)
	{
		puts("lexer_quote");
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
		printf("lex quote = %d\n", lex->quote);
		if (lex->buffer[lex->i] == lex->quotetype)
		{
			lex->state = LEX_ST_WD;
			lex->quote = 0;
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
				if (lex->startqu || (lex->foot && lex->foot->type == LEX_TP_OP))
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
			lex->quote = 1;
			lex->bgstate = LEX_ST_GEN; //pas oblige je crois
			if (lex->intoken)
				return (lexer_append(lex, LEX_TP_WD)); //voir le cas ou "\", le token n'existe pas encore....
			return (lexer_token(lex, LEX_TP_WD));
		}
		else if (lex->bgstate == LEX_ST_BLK || lex->bgstate == LEX_ST_GEN || lex->bgstate == LEX_ST_OP)
		{
			puts("mdr");
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
	if (!is_blank(lex->buffer[lex->i]) && (lex->state == LEX_ST_GEN || lex->state == LEX_ST_BLK))
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
