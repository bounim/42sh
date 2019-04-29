/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_undo_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 12:06:45 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/24 13:16:15 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	init_last_command(void)
{
	t_last_command	*head;
	t_char			*begin;
	t_char			*end;

	begin = g_shell.edit.char_list.head;
	end = g_shell.edit.char_list.tail;
	if (!(head = (t_last_command*)malloc(sizeof(t_last_command))))
		fatal_exit(SH_ENOMEM);
	head->buff = list_to_buff_print(begin, end);
	head->prev = NULL;
	g_shell.edit.last_command = head;
}

void	add_buff_to_undo(void)
{
	t_last_command	*tail;
	t_char			*begin;

	begin = g_shell.edit.char_list.head;
	if (!(tail = (t_last_command*)malloc(sizeof(t_last_command))))
		fatal_exit(SH_ENOMEM);
	tail->buff = list_to_buff_print(begin, NULL);
	tail->prev = g_shell.edit.last_command;
	g_shell.edit.last_command = tail;
}

int		compare_both_buff(t_char *begin, t_char *end, uint8_t *last_buff)
{
	uint8_t	*actual_buff;
	size_t	a_len;
	size_t	l_len;
	int		ret;

	actual_buff = list_to_buff_print(begin, end);
	a_len = ft_u8_strlen(actual_buff);
	l_len = ft_u8_strlen(last_buff);
	ret = 0;
	if (a_len != l_len)
		ret = 1;
	free(actual_buff);
	return (ret);
}

int		check_for_add_to_undo_list(uint8_t *key, size_t keylen)
{
	if (!key)
		return (1);
	if (ft_memcmp(key, CTRL__, keylen) == 0)
		return (-1);
	return (1);
}

void	add_to_undo_list(uint8_t *key, size_t keylen)
{
	if (check_for_add_to_undo_list(key, keylen) == -1)
		return ;
	if (!g_shell.edit.last_command)
		init_last_command();
	else if (compare_both_buff(g_shell.edit.char_list.head,\
		NULL, g_shell.edit.last_command->buff) != 0)
		add_buff_to_undo();
}
