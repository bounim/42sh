/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_history_actions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 17:16:59 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/04 15:03:10 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	del_charac_in_search(void)
{
	int	i;
	int	c;

	if (g_shell.hist.search_len == 0)
		return ;
	i = g_shell.hist.search_len - 1;
	c = 1;
	while (i >= 0 && g_shell.hist.search_buff[i] >= 128
			&& g_shell.hist.search_buff[i] <= 191)
	{
		i--;
		c++;
	}
	i = g_shell.hist.search_len - 1;
	g_shell.hist.search_len -= c;
	while (c-- > 0)
		g_shell.hist.search_buff[i--] = 0;
	find_in_history(0);
}

void	give_up_search(void)
{
	ft_memset(g_shell.hist.search_buff, 0, sizeof(*g_shell.hist.search_buff));
	g_shell.hist.search_len = 0;
	g_shell.edit.reading = FALSE;
	clean_and_print();
}

void	execute_search_command(void)
{
	uint8_t *buff;

	buff = g_shell.hist.search_buff;
	if (!buff[0])
		return ;
	back_to_readline();
	if (g_shell.hist.unicode_err == 1)
	{
		give_up_search();
		return ;
	}
	if (g_shell.edit.reading != 42)
		return_fn();
	g_shell.edit.reading = 42;
}

void	back_to_readline(void)
{
	t_history	*curr;
	t_history	*tail;
	int			ret;

	ret = 1;
	if (find_in_history(1) == 0)
	{
		ret = 0;
		g_shell.edit.reading = 42;
	}
	tail = g_shell.hist.history;
	while (tail && tail->next)
		tail = tail->next;
	curr = g_shell.hist.history;
	g_shell.edit.reading = FALSE;
	if (ft_carac_nb(curr->buf, ft_u8_strlen(curr->buf)) == -1)
		g_shell.hist.unicode_err = 1;
	if (ret == 1)
		print_history();
	g_shell.hist.history = tail;
	ft_memset(g_shell.hist.search_buff, 0, sizeof(*g_shell.hist.search_buff));
	g_shell.hist.search_len = 0;
	clean_and_print();
}

int		find_in_history(int save)
{
	t_history	*curr;
	int			ret;

	ret = 0;
	curr = g_shell.hist.history;
	clean_screen_from(g_shell.edit.cur_base_x, g_shell.edit.cur_base_y);
	print_search_prompt();
	if (!g_shell.hist.search_buff[0])
		return (0);
	while (curr)
	{
		if (ft_strstr((char*)curr->buf, (char*)g_shell.hist.search_buff) != 0)
		{
			if (save == 1)
			{
				g_shell.hist.history = curr;
				ret = 1;
			}
			break ;
		}
		curr = curr->bfr;
	}
	print_search_result(curr);
	return (ret);
}
