/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 15:09:53 by aguillot          #+#    #+#             */
/*   Updated: 2019/03/18 15:09:54 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static t_keymap	g_search_keymap[SEARCH_KEYMAP_SIZE] = {
	{DEL, 1, del_charac_in_search},
	{RET, 1, execute_search_command},
	{ESC, 1, give_up_search},
	{TAB, 3, back_to_readline}
};

void	build_search_buff(uint8_t *key, size_t *keylen, uint8_t *buff, size_t *buff_len)
{
	ft_memmove(buff + *buff_len, key, *keylen);
	*buff_len += *keylen;
}

void	check_printable_for_search(uint8_t *key, size_t *keylen, uint8_t *buff, size_t *buff_len)
{
	if (ft_carac_nb(key, *keylen) != -1)
	{
		if ((!(key[0] >= 0 && key[0] < 32)) || key[0] == '\n')
			build_search_buff(key, keylen, buff, buff_len);
		ft_memset(key, 0, *keylen);
		*keylen = 0;
		//clean_and_print();
		return ;
	}
}

int		search_compare_key(uint8_t *key, size_t keylen, size_t ki)
{
	if (ft_memcmp(key, g_search_keymap[ki].seq, keylen) == 0)
	{
		if (keylen == g_search_keymap[ki].len)
			return (MATCH);
		return (PARTIAL_MATCH);
	}
	return (NO_MATCH);
}

int		check_key_for_search(uint8_t *key, size_t *keylen)
{
	size_t	ki;
	int 	check;

	ki = 0;
	while (ki < sizeof(g_search_keymap) / sizeof(g_search_keymap[0]))
	{
		if ((check = search_compare_key(key, *keylen, ki)) == MATCH)
		{
			g_search_keymap[ki].funckey();
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
	uint8_t	input[1];
	uint8_t	key[6];
	size_t	keylen;
	uint8_t	buff[15000];//tester la limite
	size_t	buff_len;

	keylen = 0;
	buff_len = 0;
	ft_memset(buff, 0, sizeof(*buff));
	while (g_shell.edit.reading == TRUE)
	{
		if (read(0, input, 1) < 0)
			fatal_exit(SH_EINVAL);
		build_key(key, &keylen, input);
		if (check_key_for_search(key, &keylen) == NO_MATCH)
		{
			check_printable_for_search(key, &keylen, buff, &buff_len);
		}
		find_in_history(buff, &buff_len);
	}
}

void	search_in_history(void)
{
	//free_all;
	clean_screen();
	ft_putstr("(reverse-i-search)`\': ");
	search_read();
}