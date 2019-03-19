/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_history_actions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 17:16:59 by aguillot          #+#    #+#             */
/*   Updated: 2019/03/18 17:17:02 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	print_search_prompt()
{
	clean_screen();
	ft_putstr("(reverse-i-search)`");
	write(1, g_shell.hist.search_buff, g_shell.hist.search_len);
	ft_putstr("\': ");
}

void	del_charac_in_search(void)
{
	int 	i;
	int 	c;

	if (g_shell.hist.search_len == 0)
		return ;
	i = g_shell.hist.search_len - 1;
	c = 1;
	while (i >= 0 && g_shell.hist.search_buff[i] >= 128 && g_shell.hist.search_buff[i] <= 191)
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

void	execute_search_command(void)
{
	printf("EXEC\n");
}

void	give_up_search(void)
{
	ft_memset(g_shell.hist.search_buff, 0, sizeof(*g_shell.hist.search_buff));
	g_shell.hist.search_len = 0;
	g_shell.edit.reading = FALSE;
}

void	back_to_readline(void)
{
	t_history 	*curr;
	t_history	*tail;

	find_in_history(1);
	tail = g_shell.hist.history;
	while (tail && tail->next)
		tail = tail->next;
	curr = g_shell.hist.history;
	g_shell.edit.reading = FALSE;
	print_history();
	g_shell.hist.history = tail;
	ft_memset(g_shell.hist.search_buff, 0, sizeof(*g_shell.hist.search_buff));	
	g_shell.hist.search_len = 0;
}

void	find_in_history(int save)
{
	t_history	*curr;

	curr = g_shell.hist.history;
	print_search_prompt();
	if (!g_shell.hist.search_buff[0])
		return ;
	while (curr)
	{
		if (ft_strstr((char*)curr->buf, (char*)g_shell.hist.search_buff) != 0)
		{
			ft_putstr((char*)curr->buf);
			if (save == 1)
				g_shell.hist.history = curr;
			break ;
		}
		curr = curr->bfr;
	}
}