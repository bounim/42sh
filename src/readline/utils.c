/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:51:58 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/26 15:12:34 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

t_char	*find_first_non_prompt(t_char *head)
{
	while (head && head->is_prompt == 1)
		head = head->next;
	return (head);
}

static size_t		get_buff_size(t_char *head)
{
	size_t	buff_size;

	buff_size = 0;
	while (head)
	{
		buff_size += head->len;
		head = head->next;
	}
	return (buff_size);
}

void	return_empty(void)
{
	uint8_t *prompt;

	write(1, "\n", 1);
	clean_screen_from(g_shell.edit.cur_base_x, g_shell.edit.cur_base_y);
	prompt = prompt_to_buff(&g_shell.edit.char_list);
 	print_prompt(prompt, ft_ustrlen(prompt));
}

void	return_fn(void)
{
	uint8_t		*buff;
	t_char		*head;
	size_t		buff_size;
	int			i;

	if ((head = find_first_non_prompt(g_shell.edit.char_list.head)) == NULL)
	{
		return_empty();
		return ;
	}
	buff_size = get_buff_size(head);
	if (!(buff = (uint8_t*)malloc(sizeof(uint8_t) * (buff_size + 2))))
		readline_errors_controler(MALLOC_ERROR);
	buff[buff_size] = '\0';
	i = 0;
	while (head)
	{
		ft_memmove(buff + i, head->charac, head->len);
		i += head->len;
		head = head->next;
	}
	//free_controler(FREE_ALL);
	write(1, "\n", 1);
	g_shell.edit.reading = FALSE;
	if ((buff = (uint8_t *)replace_exclaim((char *)buff, g_shell.hist.history, NULL, NULL)))
	{
		g_shell.hist.history = rl_add_hist(g_shell.hist.history, rl_new_hist(buff));
		g_shell.hist.history_size++;
		resize_history(g_shell.hist.history);
		g_shell.hist.history_save = -1;
		buff = (uint8_t *)ft_strfjoin((char *)buff, "\n", 0);
		buff_size = ft_u8_strlen(buff);
	}
	g_shell.line = buff;
	g_shell.line_size = buff_size;
}

void	eot_fn(void)
{
	if (g_shell.edit.char_list.tail->is_prompt == 1)
	{
		cooked_terminal();
		free_controler(FREE_ALL_AND_EXIT);
	}
	supr_charac();
}