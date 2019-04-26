/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_controler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:16:41 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/26 14:17:11 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static t_keymap	g_keymap[EDIT_MODE][KEYMAP_SIZE] = {
	{
		{CTRL_A, 1, go_to_home},
		{CTRL_B, 1, move_left},
		{CTRL_C, 1, handle_ctrl_c},
		{CTRL_D, 1, eot_fn},
		{CTRL_E, 1, go_to_end},
		{CTRL_F, 1, move_right},
		{CTRL_K, 1, delete_endline},
		{CTRL_N, 1, get_next_history},
		{CTRL_P, 1, get_prev_history},
		{CTRL_R, 1, search_in_history},
		{CTRL_T, 1, drag_char},
		{ALT_T, 2, transpose_word},
		{CTRL_U, 1, delete_backline},
		{CTRL_W, 1, delete_word_backward},
		{CTRL_P, 1, get_prev_history},
		{CTRL_N, 1, get_next_history},
		{CTRL_Y, 1, paste_copy},
		{CTRL__, 1, undo_last_edit_command},
		{CTRL_X_CTRL_X, 2, exchange_point_mark},
		{ESC_B, 2, jump_word_backward},
		{ESC_D, 2, delete_word_forward},
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
		{CPY_CURR_WORD, 2, copy_current_word},
		{CPY_ALL_LINE, 2, copy_all_line},
		{PASTE, 2, paste_copy},
		{RET, 1, return_fn},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
	},
	{
		{RET, 1, return_fn},
		{DEL, 1, del_charac},
		{CTRL_C, 1, handle_ctrl_c},
		{CTRL_U, 1, delete_backline},
		{ESC, 1, vi_command_mode},
		{RIGHT_ARROW, 3, vi_move_next_char},
		{LEFT_ARROW, 3, vi_move_prev_char},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL},
		{NULL, 0, NULL}
	},
	{
		{RIGHT_ARROW, 3, vi_move_next_char},
		{LEFT_ARROW, 3, vi_move_prev_char},
		{RET, 1, return_fn},
		{"#", 1, treat_as_comment},
		{" ", 1, vi_move_next_char},
		{"v", 1, invoke_vi},
		{"j", 1, vi_get_next_history},
		{"k", 1, vi_get_prev_history},
		{"l", 1, vi_move_next_char},
		{"h", 1, vi_move_prev_char},
		{"w", 1, vi_forward_word},
		{"W", 1, vi_forward_bigword},
		{"e", 1, vi_end_word},
		{"E", 1, vi_end_bigword},
		{"b", 1, vi_backward_word},
		{"B", 1, vi_backward_bigword},
		{"^", 1, vi_move_first_nonblank},
		{"$", 1, vi_go_to_end},
		{"0", 1, go_to_home},
		{"|", 1, vi_move_counth_char},
		{"f", 1, vi_search_char_after},
		{"F", 1, vi_search_char_before},
		{"T", 1, vi_search_char_before_after},
		{"t", 1, vi_search_char_after_before},
		{";", 1, repeat_last_search_char},
		{",", 1, repeat_last_search_char_reverse},
		{"a", 1, vi_append_mode},
		{"A", 1, vi_append_eol},
		{"i", 1, vi_insert_mode},
		{"I", 1, vi_insert_bol},
		{"r", 1, vi_replace_char},
		{"R", 1, vi_replace},
		{"c", 1, vi_delete_c},
		{"C", 1, vi_delete_endline_insert_eol},
		{"S", 1, vi_clear_line_insert},
		{"x", 1, vi_delete_x},
		{"X", 1, vi_delete_bigx},
		{"d", 1, vi_delete_motion},
		{"D", 1, delete_endline},
		{"y", 1, vi_yank_motion},
		{"Y", 1, vi_yank_endline},
		{"p", 1, vi_paste_after},
		{"P", 1, vi_paste_before},
		{"u", 1, vi_undo},
		{"U", 1, vi_undo_all},
		{"+", 1, vi_get_next_history},
		{"-", 1, vi_get_prev_history}
	}
};

static int	compare_key(uint8_t *key, size_t keylen, size_t ki)
{
	if (ft_memcmp(key, g_keymap[g_shell.edit.edit_mode][ki].seq, keylen) == 0)
	{
		if (keylen == g_keymap[g_shell.edit.edit_mode][ki].len)
			return (MATCH);
		return (PARTIAL_MATCH);
	}
	return (NO_MATCH);
}

static int	check_key(uint8_t *key, size_t *keylen)
{
	size_t	ki;
	int		check;

	ki = 0;
	while (g_keymap[g_shell.edit.edit_mode][ki].seq)
	{
		if ((check = compare_key(key, *keylen, ki)) == MATCH)
		{
			add_to_undo_list(key, *keylen);
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

static void	check_printable(uint8_t *key, size_t *keylen)
{
	if (ft_carac_nb(key, *keylen) != -1)
	{
		if ((!(key[0] >= 0 && key[0] < 32)) || key[0] == '\n')
		{
			if (g_shell.edit.edit_mode == MODE_EMACS)
				add_to_undo_list(NULL, 0);
			add_char_to_list(key, *keylen, 0);
		}
		ft_memset(key, 0, *keylen);
		*keylen = 0;
		clean_and_print();
		return ;
	}
}

void		input_controller(void)
{
	uint8_t	key[6];
	size_t	keylen;
	ssize_t	rd;

	keylen = 0;
	while (g_shell.edit.reading == TRUE)
	{
		if (g_shell.edit.edit_mode == MODE_EMACS)
		{
			if (read(0, &key[keylen++], 1) < 0)
				fatal_exit(SH_EINVAL);
			if (check_key(key, &keylen) == NO_MATCH)
				check_printable(key, &keylen);
		}
		else
		{
			if ((rd = read(0, key, 6)) < 0)
				fatal_exit(SH_EINVAL);
			keylen = (size_t)rd;
			build_count(key, &keylen, g_shell.edit.edit_mode);
			if (check_key(key, &keylen) == NO_MATCH
			&& g_shell.edit.edit_mode != MODE_VI_COMMAND)
				check_printable(key, &keylen);
		}
	}
}
