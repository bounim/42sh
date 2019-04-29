/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 18:00:03 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/22 15:55:35 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITING_H
# define LINE_EDITING_H

# include <stdint.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
# include "libft.h"

/*
*** DEFINE PROMPT IDENTIFIERS
*/

enum					e_prompt
{
	BASIC_PROMPT = 0,
	QUOTE_PROMPT,
	BACKSLASH_PROMPT,
	HEREDOC_PROMPT,
};

/*
*** DEFINE SHORTCUTS
*/

# define BASIC_PRMPT "<21sh> "
# define QUOTE_PRMPT "pquote> "
# define BACKSLASH_PRMPT "> "
# define HEREDOC_PRMPT "heredoc> "
# define SEARCH_PRMPT "(reverse-i-search)`"
# define MATCH 1
# define PARTIAL_MATCH 0
# define NO_MATCH -1
# define NBSP "\302\240"
# define MULTI 2

/*
*** DEFINE VI SHORTCUTS
*/

enum					e_vi_search
{
	SEARCH_CHAR_AFTER = 0,
	SEARCH_CHAR_BEFORE,
	SEARCH_CHAR_AFTER_BEFORE,
	SEARCH_CHAR_BEFORE_AFTER
};

/*
*** DEFINE ERROR CODES
*/

enum					e_errnum
{
	PRINT_USAGE = 0,
	NO_TERM_ENV,
	NO_TERM_INFO,
	MALLOC_ERROR,
	EXIT
};

/*
*** DEFINE FREE CODES
*/

enum					e_freenum
{
	FREE_ALL_AND_EXIT = 0,
	FREE_ALL_EDIT,
	FREE_ONLY_EDIT_CHAR_LIST
};

/*
*** DEFINE CARACTERS SEQUENCES
*/

# define CTRL_A "\001"
# define CTRL_B "\002"
# define CTRL_C "\003"
# define CTRL_D "\004"
# define CTRL_E "\005"
# define CTRL_F "\006"
# define CTRL_K "\013"
# define CTRL_N "\016"
# define CTRL_P "\020"
# define CTRL_R "\022"
# define CTRL_U "\025"
# define CTRL_Y "\031"
# define CTRL_W "\027"
# define CTRL_T "\024"
# define CTRL__ "\037"
# define ALT_T "\033t"
# define CTRL_X_CTRL_X "\030\030"
# define TAB "\011"
# define ESC "\033"
# define ESC_B "\033b"
# define ESC_F "\033f"
# define ESC_D "\033d"
# define RET "\012"
# define DEL "\177"
# define CPY_CURR_WORD "\033c"
# define CPY_ALL_LINE "\033a"
# define PASTE "\033v"
# define SUPR "\033[3~"
# define UP_LINE "\033u"
# define DOWN_LINE "\033d"
# define UP_ARROW "\033[A"
# define DOWN_ARROW "\033[B"
# define RIGHT_ARROW "\033[C"
# define LEFT_ARROW "\033[D"
# define HOME "\033[H"
# define END "\033[F"
# define FORWARD_WORD "\033f"
# define BACKWARD_WORD "\033b"

/*
*** DEFINE STRUCTS
*/

typedef struct s_char	t_char;

struct					s_char
{
	uint8_t				charac[6];
	size_t				len;
	uint32_t			x_pos;
	int					y_pos;
	int					is_prompt;
	struct s_char		*prev;
	struct s_char		*next;
};

typedef struct s_cpy	t_cpy;

struct					s_cpy
{
	uint8_t				charac[6];
	size_t				len;
	t_cpy				*next;
};

typedef struct			s_char_list
{
	t_char				*head;
	t_char				*tail;
	uint32_t			char_nb;
}						t_char_list;

typedef void			(*t_key_func)(void);

typedef struct			s_keymap
{
	char				*seq;
	size_t				len;
	t_key_func			funckey;
}						t_keymap;

typedef struct			s_term
{
	struct winsize		max;
}						t_term;

struct					s_last_command
{
	uint8_t				*buff;
	t_last_command		*prev;
};

typedef struct			s_edit
{
	t_char				*point_char;
	t_char				*mark;
	t_last_command		*last_command;
	t_char_list			char_list;
	t_term				term_info;
	int					prompt_id;
	int					reading;
	int					ret_ctrl_c;
	int					count;
	int					edit_mode;
	size_t				cur_base_x;
	int					cur_base_y;
	int					lines_to_shift;
	uint8_t				*cpy_buff;
	int					vi_last_search_fn;
	uint8_t				vi_last_search_char;
}						t_edit;

/*
*** Signals handling functions for readline part
*/

void					init_signals(void);
void					clear_signals(void);
void					signal_handler(int signo);

/*
*** Readline init functions
*/
void					init_prompt(int prompt_id);
void					init_char_list(void);
void					init_edit(void);
void					init_prompt(int prompt_id);
int						get_term_pos(size_t *line, size_t *col);
void					readline(int prompt_id);

/*
*** Termcaps and terminal modification functions
*/
void					modify_term(void);
void					reset_term(void);

/*
*** Charac list use functions
*/
void					add_char_to_list(uint8_t *charac, size_t len,\
		int is_prompt);
void					delete_char_from_list(t_char *charac);

/*
*** Position Calculation function for each character on screen
*/
size_t					get_x_pos(t_char *prev_char, uint32_t col_limit);
size_t					get_y_pos(t_char *prev_char, uint32_t col_limit,\
		uint32_t row_limit);
void					place_base_at_start(void);
void					update_all_pos(void);
void					shift_pos_up(void);
void					shift_pos_down(void);
t_char					*skip_prompt(t_char *head);

/*
***
*/
int						get_buf_size(t_char *head, t_char *end);
uint8_t					*list_to_buff_print(t_char *curr, t_char *end);
uint8_t					*prompt_to_buff(t_char_list *list);
void					print_prompt(uint8_t *prompt, size_t prompt_len);
int						get_prompt_len(int prompt_id);
void					clean_screen_from(int x, int y);
void					clean_and_print(void);
void					input_controller(void);
void					readline_errors_controler(int errnum);

/*
*** Movement functions for readline
*/
void					move_up(void);
void					move_down(void);
void					move_right(void);
void					move_left(void);
void					go_to_home(void);
void					go_to_end(void);
void					jump_word_forward(void);
void					jump_word_backward(void);
void					exchange_point_mark(void);

/*
*** Delete functions for readline in EMACS mode
*/
void					del_charac(void);
void					supr_charac(void);
void					delete_backline(void);
void					delete_endline(void);
void					delete_word_forward(void);
void					delete_word_backward(void);
void					drag_char(void);
size_t					go_back_one_car(uint8_t *buff, size_t index);
int						transpose_word_conditions(t_char *curr);
t_char					*get_to_right_position(t_char *curr);
void					transpose_word(void);
uint8_t					*build_cpy_buff(t_char *cpy_begin, t_char *cpy_end);
void					eot_fn(void);

/*
*** Copy functions for readline
*/
int						copy_current_word_start_conditions(t_char *curr);
int						copy_current_word_begin_conditions(t_char *curr);
int						copy_current_word_end_conditions(t_char *curr);
void					copy_current_word(void);
void					copy_all_line(void);
void					paste_copy(void);

/*
*** Readline special action functions
*/
void					return_fn(void);
t_char					*find_first_non_prompt(t_char *head);
void					rl_free_controler(int code);
void					free_last_command_list(void);
void					place_cursor_after_print(t_char *curr, int max_x,\
		int max_y);
void					handle_ctrl_c(void);
void					add_to_undo_list(uint8_t *key, size_t keylen);
void					undo_last_edit_command(void);
void					delete_last_command(t_last_command *last);
void					build_count(uint8_t *key, size_t *keylen, int mode);

/*
*** VIM function for VIM mode in readline
*/
void					vi_command_mode(void);
void					vi_move_next_char(void);
void					vi_move_prev_char(void);
void					treat_as_comment(void);
void					invoke_vi(void);
void					vi_get_next_history(void);
void					vi_get_prev_history(void);
void					vi_forward_word(void);
void					vi_forward_bigword(void);
void					vi_end_word(void);
void					vi_end_bigword(void);
void					vi_backward_word(void);
void					vi_backward_bigword(void);
void					vi_move_first_nonblank(void);
void					vi_move_counth_char(void);
void					vi_search_char_after(void);
void					vi_search_char_before(void);
void					vi_search_char_after_before(void);
void					vi_search_char_before_after(void);
void					repeat_last_search_char(void);
void					repeat_last_search_char_reverse(void);
void					vi_repeat_after(uint8_t charac);
void					vi_repeat_before(uint8_t charac);
void					vi_repeat_after_before(uint8_t charac);
void					vi_repeat_before_after(uint8_t charac);
void					vi_append_mode(void);
void					vi_append_eol(void);
void					vi_insert_mode(void);
void					vi_insert_bol(void);
void					vi_replace_char(void);
void					vi_replace(void);
void					vi_delete_c(void);
void					vi_delete_endline_insert_eol(void);
void					vi_clear_line_insert(void);
void					vi_delete_x(void);
void					vi_delete_bigx(void);
void					vi_go_to_end(void);
void					vi_paste_after(void);
void					vi_paste_before(void);
void					vi_yank_motion(void);
void					vi_yank_endline(void);
void					vi_undo(void);
void					vi_undo_all(void);
void					vi_delete_motion(void);

#endif
