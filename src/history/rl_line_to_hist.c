/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_line_to_hist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:59:38 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/23 19:18:41 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void		append_line_to_hist(int is_multi, uint8_t *buff)
{
	uint8_t *hist_buff;

	hist_buff = g_shell.hist.history->buf;
	if (is_multi == MULTI)
		hist_buff = (uint8_t*)ft_strfjoin((char*)hist_buff, "\n", 0);
	hist_buff = (uint8_t*)ft_strfjoin((char*)hist_buff, (char*)buff, 0);
	g_shell.hist.history->buf = hist_buff;
}

static void		create_new_hist_line(uint8_t *buff)
{
	t_history	*curr;

	if (!(curr = find_last_hist_line()))
		curr = g_shell.hist.history;
	g_shell.hist.history = rl_add_hist(curr, rl_new_hist(buff));
	g_shell.hist.history_size++;
	resize_history(g_shell.hist.history);
	g_shell.hist.history_save = -1;
}

void			rl_line_to_hist(int add_to_hist, uint8_t *buff)
{
	if (g_shell.edit.prompt_id != HEREDOC_PROMPT && add_to_hist == 1)
	{
		if (g_shell.edit.prompt_id == QUOTE_PROMPT)
			append_line_to_hist(MULTI, buff);
		else if (g_shell.edit.prompt_id == BACKSLASH_PROMPT)
			append_line_to_hist(1, buff);
		else
			create_new_hist_line(buff);
	}
}
