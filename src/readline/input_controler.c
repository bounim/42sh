/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_controler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:16:41 by aguillot          #+#    #+#             */
/*   Updated: 2019/03/11 14:00:15 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static t_keymap	g_keymap[EDIT_MODE][KEYMAP_SIZE] = {
	{
		{CTRL_B, 1, move_left},
		{CTRL_A, 1, go_to_home},
		{CTRL_E, 1, go_to_end},
		{CTRL_F, 1, move_right},
		{CTRL_U, 1, delete_backline},
		{CTRL_K, 1, delete_endline},
		{CTRL_X_CTRL_X, 2, exchange_point_mark},
		{ESC_B, 2, jump_word_backward},
		{ESC_F, 2, jump_word_forward},
		{RIGHT_ARROW, 3, move_right},
		{LEFT_ARROW, 3, move_left},
		{UP_ARROW, 3, get_prev_history},
		{DOWN_ARROW, 3, get_next_history},
		{UP_LINE, 2, move_up},
		{DOWN_LINE, 2, move_down},
		{HOME, 3, go_to_home},
		{END, 3, go_to_end},
		{FORWARD_WORD, 2, jump_word_forward},
		{BACKWARD_WORD, 2, jump_word_backward},
		{DEL, 1, del_charac},
		{SUPR, 4, supr_charac},
		{EOT, 1, eot_fn},
		{CPY_CURR_WORD, 2, copy_current_word},
		{CPY_ALL_LINE, 2, copy_all_line},
		{PASTE, 2, paste_copy},
		{RET, 1, return_fn}
	}
};

int		compare_key(uint8_t *key, size_t keylen, size_t ki)
{
	if (ft_memcmp(key, g_keymap[g_shell.edit.edit_mode][ki].seq, keylen) == 0)
	{
		if (keylen == g_keymap[g_shell.edit.edit_mode][ki].len)
			return (MATCH);
		return (PARTIAL_MATCH);
	}
	return (NO_MATCH);
}

int		check_key(uint8_t *key, size_t *keylen)
{
	size_t	ki;
	int 	check;

	ki = 0;
	while (ki < sizeof(g_keymap[g_shell.edit.edit_mode]) / sizeof(g_keymap[g_shell.edit.edit_mode][0]))
	{
		if ((check = compare_key(key, *keylen, ki)) == MATCH)
		{
			g_keymap[g_shell.edit.edit_mode][ki].funckey();
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

void	check_printable(uint8_t *key, size_t *keylen)
{
	if (ft_carac_nb(key) != -1)
	{
		if ((!(key[0] >= 0 && key[0] < 32)) || key[0] == '\n')
			add_char_to_list(key, *keylen, 0);
		ft_memset(key, 0, *keylen);
		*keylen = 0;
		clean_and_print();
		return ;
	}
}

void	build_key(uint8_t *key, size_t *keylen, uint8_t *input)
{
	*(key + *keylen) = *input;
	(*keylen)++;
}

void	input_controller(void)
{
	uint8_t	input[1];
	uint8_t	key[6];
	size_t	keylen;

	keylen = 0;
	while (read(0, input, 1) > 0)
	{
		build_key(key, &keylen, input);
		if (check_key(key, &keylen) == NO_MATCH)
			check_printable(key, &keylen);
	}
}
