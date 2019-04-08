/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_readline_return.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:36:40 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/06 14:58:02 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	put_prompt_in_simple_buff(uint8_t *simple_buff, int prompt_id, int len)
{
	if (prompt_id == BASIC_PROMPT)
		ft_memmove(simple_buff, BASIC_PRMPT, len);
	else if (prompt_id == QUOTE_PROMPT)
		ft_memmove(simple_buff, QUOTE_PRMPT, len);
	else if (prompt_id == BACKSLASH_PROMPT)
		ft_memmove(simple_buff, BACKSLASH_PRMPT, len);
	else if (prompt_id == HEREDOC_PROMPT)
		ft_memmove(simple_buff, HEREDOC_PRMPT, len);
}

void	simple_readline_return(uint8_t *buff, int len)
{
	g_shell.line = buff;
	g_shell.line_size = len;
	g_shell.edit.reading = FALSE;
}
