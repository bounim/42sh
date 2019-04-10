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

int 	buff_is_prompt(uint8_t *buff, int len)
{
	uint8_t	*prompt;
	int		p_len;
	int		prompt_id;

	prompt_id = g_shell.edit.prompt_id;
	p_len = get_prompt_len(prompt_id);
	if (!(prompt = (uint8_t*)malloc(sizeof(uint8_t) * (p_len + 1))))
		fatal_exit(SH_ENOMEM);
	prompt[p_len] = '\0';
	put_prompt_in_simple_buff(prompt, prompt_id, p_len);
	if (p_len == len && ft_memcmp(buff, prompt, len) == 0)
	{
		free(prompt);
		return (1);
	}
	free(prompt);
	return (0);
}

void	simple_rl_eot_fn(uint8_t *buff, int len)
{
	if (buff_is_prompt(buff, len) == 1)
	{
		cooked_terminal();
		free_controler(FREE_ALL_AND_EXIT);
	}
}

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