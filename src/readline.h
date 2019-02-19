/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 15:28:17 by schakor           #+#    #+#             */
/*   Updated: 2019/02/16 10:53:57 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include "rl_defines.h"
# include "rl_typedefs.h"

/*
**		readline utility that allows the user to edit the command line
*/

struct					s_keymap
{
	char				*key;
	t_rl_command_func	rl_command_func;
};

struct					s_bufvar
{
	size_t				i_char;
	size_t				len_char;
	size_t				i_buf;
	size_t				len_buf;
	size_t				len_tot;
};

struct					s_history
{
	uint8_t					*buf;
	t_bufvar				bufvar;
	t_history				*next;
	t_history				*bfr;
};

struct					s_rl
{
	char				*prompt;
	size_t				len_prompt;
	uint8_t				*buf;
	t_bufvar			bufvar;
	uint8_t				bufkey[8];
	size_t				bufkey_index;
	int					keymap_index;
	t_history			*history;
	t_bool				reading;
	int					history_save;
	int					history_size;

};

void					readline(void);
void					rl_get_prompt(t_rl *rl);
void					rl_display_prompt(const char *prompt);
void					rl_insert_buffer(t_rl *rl, unsigned char c);
void					rl_increase_buffer(t_rl *rl);
void					rl_move_start(t_rl *rl);
void					rl_backward_char(t_rl *rl);
void					rl_forward_char(t_rl *rl);
void					rl_delete_buffer(t_rl *rl);
int						get_nb_bytes(t_rl *rl, int index);
void					rl_backward_word(t_rl *rl);
void					rl_forward_word(t_rl *rl);
void					rl_beg_of_line(t_rl *rl);
void					rl_end_of_line(t_rl *rl);
void					rl_ctrl_x_x(t_rl *rl);
void					rl_delete_underneath(t_rl *rl);
void					rl_delete_backline(t_rl *rl);
void					rl_delete_endline(t_rl *rl);
void					rl_delete_esc_d(t_rl *rl);
void					rl_delete_ctrl_w(t_rl *rl);
void					rl_ctrl_d(t_rl *rl);
void					rl_get_next_history(t_rl *rl);
void					rl_get_prev_history(t_rl *rl);
void					rl_add_history(t_rl *rl);
void					rl_end_of_read(t_rl *rl);
void					rl_switch_history(t_rl *rl);
void					rl_print_history(t_rl *rl);
t_history				*rl_new_hist(uint8_t *buffer, t_bufvar bufvar);
t_history				*rl_add_hist(t_history *list, t_history *new_hist);
void					rl_history_from_file(t_rl *rl, char *path);
void					rl_file_from_history(t_rl *rl, char *path);
int						listlen(t_history *list);
void					rl_ctrl_c(t_rl *rl);

#endif
