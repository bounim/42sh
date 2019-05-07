/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_script2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 06:07:37 by emartine          #+#    #+#             */
/*   Updated: 2019/05/07 06:07:38 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int				script_heredoc_copy(t_lexer_token *heredoc, size_t *i,
		uint8_t *buf, size_t size)
{
	uint8_t	*hbuf;
	size_t	j;

	j = *i;
	while (j < size && buf[j] != '\n')
		j++;
	if (j - *i == heredoc->next->size && ft_memcmp(buf + *i,
				heredoc->next->buffer, heredoc->next->size) == 0)
	{
		*i = j + 1;
		return (0);
	}
	if (NULL == (hbuf = malloc(heredoc->heredoc_size + j - *i + 1)))
		return (-1);
	ft_memmove(hbuf, heredoc->heredoc_buffer, heredoc->heredoc_size);
	ft_memmove(hbuf + heredoc->heredoc_size, buf + *i, j - *i);
	hbuf[heredoc->heredoc_size + (j - *i)] = '\n';
	free(heredoc->heredoc_buffer);
	heredoc->heredoc_buffer = hbuf;
	heredoc->heredoc_size += j - *i + 1;
	*i = j + 1;
	return (1);
}

int				script_lex_a_line(t_lexer *lex, size_t *i,
		uint8_t *buf, size_t size)
{
	if (*i < size)
	{
		lexer(lex, buf + *i, size - *i);
		*i += lex->i;
		return (0);
	}
	if (lex->head && !lex->input_end)
		write_error("syntax error", "unexpected end of file");
	return (-1);
}
