/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_search.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 12:28:56 by aguillot          #+#    #+#             */
/*   Updated: 2019/03/25 12:28:59 by aguillot         ###   ########.fr       */
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
//PB: Quand tu print lls puis tu rajoutes un l apres, ca fait qquchose qui n'est pas dans l'histo, ca fait curr_y--;
//Le pb c'est que je ne garde pas le nbre de lignes donc il rajoute des y tout le temps
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
		if ((in_line % one_line == 0 || full_buff[i] == '\n'))
		{
			y_pos++;
			if (y_pos >= g_shell.edit.term_info.max.ws_row)
				g_shell.edit.cur_base_y--;
			if (full_buff[i] == '\n')
				in_line = 0;
			if (!full_buff[i + 1])
				write(1, "\n", 1);
		}
		in_line++;
		i += ft_wchar_len(full_buff + i);
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
	clean_screen_from(g_shell.edit.cur_base_x, g_shell.edit.cur_base_y);
	if (curr)
		update_base_y_in_search(curr->buf);
	else
		update_base_y_in_search(NULL);
	print_search_prompt();
	if (curr)
		ft_putstr((char*)curr->buf);
}