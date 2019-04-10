/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_fn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:51:35 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/02 18:36:03 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void	return_end(uint8_t *buff, size_t buff_size)
{
	free_controler(FREE_ALL_EDIT);
	write(1, "\n", 1);
	ft_putstr(tgetstr("cr", NULL));
	g_shell.edit.reading = FALSE;
	if ((buff = (uint8_t *)replace_exclaim((char *)buff,\
					g_shell.hist.history, NULL, NULL)))
	{
		g_shell.hist.history = rl_add_hist(g_shell.hist.history,\
				rl_new_hist(buff));
		g_shell.hist.history_size++;
		resize_history(g_shell.hist.history);
		g_shell.hist.history_save = -1;
		buff = (uint8_t *)ft_strfjoin((char *)buff, "\n", 0);
		buff_size = ft_u8_strlen(buff);
	}
	g_shell.line = buff;
	g_shell.line_size = buff_size;
}

void		return_fn(void)
{
	uint8_t		*buff;
	t_char		*head;
	size_t		buff_size;
	int			i;

	if ((head = find_first_non_prompt(g_shell.edit.char_list.head)) == NULL)
		buff_size = 0;
	else
		buff_size = get_buf_size(head, g_shell.edit.char_list.tail);
	if (!(buff = (uint8_t*)malloc(sizeof(uint8_t) * (buff_size + 2))))
		readline_errors_controler(MALLOC_ERROR);
	buff[buff_size] = '\n';
	buff[buff_size + 1] = '\0';
	buff_size++;
	i = 0;
	while (head)
	{
		ft_memmove(buff + i, head->charac, head->len);
		i += head->len;
		head = head->next;
	}
	return_end(buff, buff_size);
}
