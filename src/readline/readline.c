/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 18:04:47 by schakor           #+#    #+#             */
/*   Updated: 2019/02/19 14:07:10 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static t_keymap				g_keymap[MODES][KEYMAP_SIZE] = {
	{
		{KEYSTR_CTRL_A, rl_beg_of_line},
		{KEYSTR_CTRL_B, rl_backward_char},
		{KEYSTR_CTRL_C, rl_ctrl_c},
		{KEYSTR_CTRL_D, rl_ctrl_d},
		{KEYSTR_CTRL_E, rl_end_of_line},
		{KEYSTR_CTRL_F, rl_forward_char},
		{KEYSTR_ESC_B, rl_backward_word},
		{KEYSTR_ESC_F, rl_forward_word},
		{KEYSTR_CTRL_X_X, rl_ctrl_x_x},
		{KEYSTR_BACKSPACE, rl_delete_buffer},
		{KEYSTR_DEL, rl_delete_underneath},
		{KEYSTR_CTRL_U, rl_delete_backline},
		{KEYSTR_CTRL_K, rl_delete_endline},
		{KEYSTR_ESC_D, rl_delete_esc_d},
		{KEYSTR_CTRL_W, rl_delete_ctrl_w},
		{KEYSTR_LEFT_ARROW, rl_backward_char},
		{KEYSTR_RIGHT_ARROW, rl_forward_char},
		{KEYSTR_UP_ARROW, rl_get_prev_history},
		{KEYSTR_DOWN_ARROW, rl_get_next_history},
		{KEYSTR_HOME, rl_beg_of_line},
		{KEYSTR_END, rl_end_of_line},
		{KEYSTR_RETURN, rl_end_of_read}

	},
	{
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL}
	},
	{
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL},
		{NULL, NULL}
	}
};

static int					find_key_in_keymap(t_rl *rl)
{
	int						i;
	int						cmp;
	int 					mode = g_shell.el_mode;

	i = 0;
	while (i < KEYMAP_SIZE)
	{
		cmp = ft_memcmp(g_keymap[mode][i].key, rl->bufkey, rl->bufkey_index);
		if (cmp == 0 && rl->bufkey_index == ft_strlen(g_keymap[mode][i].key))
		{
			rl->keymap_index = i;
			return (PERFECT_KEY_MATCH);
		}
		else if (cmp == 0)
			return (PARTIAL_KEY_MATCH);
		i++;
	}
	return (NO_KEY_MATCH);
}

static void					read_stdin(t_rl *rl)
{
	t_bool					stop;
	int						find_key;

	stop = FALSE;
	rl->keymap_index = -1;
	rl->bufkey_index = 0;
	ft_memset(rl->bufkey, 0, 8);
	while (stop == FALSE)
	{
		if (read(STDIN_FILENO, &rl->bufkey[rl->bufkey_index++], 1) < 0)
			fatal_exit(SH_ENOMEM);
		//printf("%d\n", rl->bufkey[rl->bufkey_index - 1]);
		find_key = find_key_in_keymap(rl);
		if (find_key == PERFECT_KEY_MATCH)
			stop = TRUE;
		else if (find_key == NO_KEY_MATCH)
			stop = TRUE;
	}
}

static void					rl_main_work(t_rl *rl)
{
	while (rl->reading == TRUE)
	{
		read_stdin(rl);
		if (rl->keymap_index >= 0)
			g_keymap[g_shell.el_mode][rl->keymap_index].rl_command_func(rl);
		else if (rl->keymap_index == -1)
			rl_insert_buffer(rl, rl->bufkey[0]);
		if (rl->bufvar.len_buf >= rl->bufvar.len_tot)
			rl_increase_buffer(rl);
	}
}

static void					rl_init(t_rl *rl)
{
	if (!(rl->buf = (uint8_t *)ft_memalloc(BUF_TMP + 1)))
		fatal_exit(SH_ENOMEM);
	rl->bufvar.i_char = 0;
	rl->bufvar.len_char = 0;
	rl->bufvar.i_buf = 0;
	rl->bufvar.len_buf = 0;
	rl->bufvar.len_tot = BUF_TMP;
	ft_memset(rl->bufkey, 0, sizeof(rl->bufkey));
	rl->bufkey_index = 0;
	rl->reading = TRUE;
	rl->history = g_shell.history;
	rl->history_size = g_shell.history_size;
	rl->history_save = g_shell.history_save;
}

void						readline()
{
	t_rl					rl;

	raw_terminal();
	rl_init(&rl);
	rl_get_prompt(&rl);
	rl_display_prompt(rl.prompt);
	rl_main_work(&rl);
	g_shell.line = rl.buf;
	g_shell.history = rl.history;
	g_shell.history_size = rl.history_size;
	g_shell.history_save = rl.history_save;
	free(rl.prompt);
	cooked_terminal();
}