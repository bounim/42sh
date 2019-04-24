/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 15:09:53 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/22 16:09:00 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static t_searchmap	g_searchmap[SEARCHMAP_SIZE] = {
	{DEL, 1, del_charac_in_search},
	{RET, 1, execute_search_command},
	{ESC, 1, give_up_search},
	{TAB, 1, back_to_readline}
};

void	check_printable_for_search(uint8_t *key, size_t *keylen)
{
	if (ft_carac_nb(key, *keylen) != -1)
	{
		if ((!(key[0] >= 0 && key[0] < 32)) || key[0] == '\n')
			build_search_buff(key, keylen);
		ft_memset(key, 0, *keylen);
		*keylen = 0;
		return ;
	}
}

int		search_compare_key(uint8_t *key, size_t keylen, size_t ki)
{
	if (ft_memcmp(key, g_searchmap[ki].seq, keylen) == 0)
	{
		if (keylen == g_searchmap[ki].len)
			return (MATCH);
		return (PARTIAL_MATCH);
	}
	return (NO_MATCH);
}

int		check_key_for_search(uint8_t *key, size_t *keylen)
{
	size_t	ki;
	int		check;

	ki = 0;
	while (ki < sizeof(g_searchmap) / sizeof(g_searchmap[0]))
	{
		if ((check = search_compare_key(key, *keylen, ki)) == MATCH)
		{
			g_searchmap[ki].searchfunc();
			ft_memset(key, 0, *keylen);
			*keylen = 0;
			return (MATCH);
		}
		if (check == PARTIAL_MATCH)
			return (PARTIAL_MATCH);
		ki++;
	}
	return (NO_MATCH);
}

void	search_read(void)
{
	uint8_t	key[6];
	size_t	keylen;

	keylen = 0;
	while (g_shell.edit.reading == TRUE)
	{
		if (read(0, &key[keylen++], 1) < 0)
			fatal_exit(SH_EINVAL);
		if (check_key_for_search(key, &keylen) == NO_MATCH)
		{
			check_printable_for_search(key, &keylen);
			find_in_history(0);
		}
	}
}

void	search_in_history(void)
{
	if (!g_shell.hist.history)
		return ;
	g_shell.hist.unicode_err = 0;
	clean_screen_from(g_shell.edit.cur_base_x, g_shell.edit.cur_base_y);
	ft_putstr("(reverse-i-search)`\': ");
	search_read();
	if (g_shell.edit.reading == FALSE)
		g_shell.edit.reading = TRUE;
	else
		g_shell.edit.reading = FALSE;
}
