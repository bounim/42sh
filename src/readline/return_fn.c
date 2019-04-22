/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_fn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:51:35 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/10 17:43:45 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static uint8_t	*check_buff_end_for_b(uint8_t *buff, size_t buff_size)
{
	if (buff_size <= 0)
		return (buff);
	if (buff[buff_size - 1] == '\\')
		buff[buff_size - 1] = '\0';
	return (buff);
}

static void		append_line_to_hist(int is_multi, uint8_t *buff,\
	size_t buff_size)
{
	uint8_t *hist_buff;
	uint8_t	*tmp;

	tmp = (uint8_t*)ft_strdup((char*)buff);
	tmp = check_buff_end_for_b(tmp, buff_size);
	hist_buff = g_shell.hist.history->buf;
	if (is_multi == MULTI)
		hist_buff = (uint8_t*)ft_strfjoin((char*)hist_buff, "\n", 0);
	hist_buff = (uint8_t*)ft_strfjoin((char*)hist_buff, (char*)tmp, 0);
	g_shell.hist.history->buf = hist_buff;
	free(tmp);
}

static void		create_new_hist_line(uint8_t *buff, size_t buff_size)
{
	uint8_t	*tmp;

	tmp = (uint8_t*)ft_strdup((char*)buff);
	tmp = check_buff_end_for_b(tmp, buff_size);
	g_shell.hist.history = rl_add_hist(g_shell.hist.history,\
		rl_new_hist(tmp));
	g_shell.hist.history_size++;
	resize_history(g_shell.hist.history);
	g_shell.hist.history_save = -1;
	free(tmp);
}

static void		return_end(uint8_t *buff, size_t buff_size, int add_to_hist)
{
	rl_free_controler(FREE_ALL_EDIT);
	cooked_terminal();
	write(1, "\n", 1);
	g_shell.edit.reading = FALSE;
	if ((buff = (uint8_t *)replace_exclaim((char *)buff,\
					g_shell.hist.history, NULL, NULL)))
	{
		if (g_shell.edit.prompt_id != HEREDOC_PROMPT
			&& add_to_hist == 1)
		{
			if (g_shell.edit.prompt_id == QUOTE_PROMPT)
				append_line_to_hist(MULTI, buff, buff_size);
			else if (g_shell.edit.prompt_id == BACKSLASH_PROMPT)
				append_line_to_hist(1, buff, buff_size);
			else
				create_new_hist_line(buff, buff_size);
		}
		buff = (uint8_t *)ft_strfjoin((char *)buff, "\n", 0);
		buff_size = ft_u8_strlen(buff);
	}
	g_shell.line = buff;
	g_shell.line_size = buff_size;
}

void			return_fn(void)
{
	uint8_t		*buff;
	t_char		*head;
	size_t		buff_size;
	int			i;

	if ((head = find_first_non_prompt(g_shell.edit.char_list.head)) == NULL)
		buff_size = 0;
	else
		buff_size = get_buf_size(head, NULL);
	if (!(buff = (uint8_t*)malloc(sizeof(uint8_t) * (buff_size + 1))))
		readline_errors_controler(MALLOC_ERROR);
	buff[buff_size] = '\0';
	i = 0;
	while (head)
	{
		ft_memmove(buff + i, head->charac, head->len);
		i += head->len;
		head = head->next;
	}
	if (g_shell.edit.char_list.tail->is_prompt == 0)
		i = 1;
	else
		i = 0;
	return_end(buff, buff_size, i);
}
