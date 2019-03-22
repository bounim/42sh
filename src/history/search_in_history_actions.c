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

// pour le update il faut reconstruire le buff en entier (prompt + search_buff + search_results) et appliquer la meme formule.

uint8_t *build_full_buff(uint8_t *hist_buff)
{
	uint8_t *full_buff;
	size_t	hist_len;
	size_t	search_len;


	hist_len = ft_u8_strlen(hist_buff);
	search_len = g_shell.hist.search_len;
	if (!(full_buff = (uint8_t*)malloc(sizeof(uint8_t) *
		(hist_len + 23 + search_len + 1))))
		fatal_exit(SH_ENOMEM);
	ft_memset(full_buff, 0, hist_len + 23 + g_shell.hist.search_len + 1);
	ft_memmove(full_buff, SEARCH_PRMPT, 19);
	ft_memmove(full_buff + 19, g_shell.hist.search_buff, g_shell.hist.search_len);
	ft_memmove(full_buff + 19 + search_len, "\': ", 3);
	if (hist_buff)
		ft_memmove(full_buff + 22 + search_len, hist_buff, hist_len);
	else
		full_buff[23 + search_len] = '\0';
	return (full_buff);
}

//le full_buff est bien construit, reste a revoir l'algo
//pb quand tu del, find in history est appelé qui a son tour appel print results, ca recalcule la pos et ca refait baisser le curr_y;
//regarder avec lls, quand tu print et que tu arrives en fin de ligne il descend pas tout seul.
void	update_base_y_in_search(uint8_t *hist_buff)
{
	uint8_t *full_buff;
	int 	i;
	int 	one_line;
	int 	in_line;
	int 	y_pos;

	full_buff = build_full_buff(hist_buff);
	i = 0;
	one_line = g_shell.edit.term_info.max.ws_col;
	in_line = 1;
	y_pos = g_shell.edit.cur_base_y;// y_pos commence a 0
	while (full_buff[i])
	{
		if (in_line % one_line == 0 || full_buff[i] == '\n')
		{
			y_pos++;
			if (y_pos + 1 >= g_shell.edit.term_info.max.ws_row)
				g_shell.edit.cur_base_y--;
			if (full_buff[i] == '\n')
				in_line = 0;
		}
		in_line++;
		i++;
	}
	free(full_buff);
}

void	print_search_prompt(void)
{
	write(1, SEARCH_PRMPT, 19);
	write(1, g_shell.hist.search_buff, g_shell.hist.search_len);
	ft_putstr("\': ");
}

void	print_search_result(t_history *curr)
{
	clean_screen();
	if (curr)
		update_base_y_in_search(curr->buf);
	else
		update_base_y_in_search(NULL);
	print_search_prompt();
	if (curr)
		ft_putstr((char*)curr->buf);
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
	return_fn();
	g_shell.edit.reading = 42;
}

void 	back_to_readline(void)
{
	t_history 	*curr;
	t_history	*tail;

	find_in_history(1);
	tail = g_shell.hist.history;
	while (tail && tail->next)
		tail = tail->next;
	curr = g_shell.hist.history;
	g_shell.edit.reading = FALSE;
	if (ft_carac_nb(curr->buf, ft_u8_strlen(curr->buf)) == -1)
		g_shell.hist.unicode_err = 1;
	print_history();
	g_shell.hist.history = tail;
	ft_memset(g_shell.hist.search_buff, 0, sizeof(*g_shell.hist.search_buff));	
	g_shell.hist.search_len = 0;
	clean_and_print();
}

void	find_in_history(int save)
{
	t_history	*curr;

	curr = g_shell.hist.history;
	clean_screen();
	print_search_prompt();
	if (!g_shell.hist.search_buff[0])
		return ;
	while (curr)
	{
		if (ft_strstr((char*)curr->buf, (char*)g_shell.hist.search_buff) != 0)
		{
			if (save == 1)
				g_shell.hist.history = curr;
			break ;
		}
		curr = curr->bfr;
	}
	print_search_result(curr);
}