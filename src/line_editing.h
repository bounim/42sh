/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 18:00:03 by aguillot          #+#    #+#             */
/*   Updated: 2019/03/26 18:31:31 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITING_H
# define LINE_EDITING_H

# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
# include "libft.h"

/*
*** DEFINE PROMPT IDENTIFIERS
*/

enum 					e_prompt
{
	BASIC_PROMPT = 0,
	QUOTE_PROMPT,
	BACKSLASH_PROMPT,
	HEREDOC_PROMPT,
	SEARCH_PROMPT
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


/*
*** DEFINE ERROR CODES
*/

enum					e_errnum
{
	PRINT_USAGE = 0,
	NO_TERM_ENV, 
	NO_TERM_INFO,
	CANT_MODIFY_TERM,
	MALLOC_ERROR,
	EXIT
};

/*
*** DEFINE FREE CODES
*/

enum 					e_freenum
{
	FREE_ALL_AND_EXIT = 0,
	FREE_ALL
};

/*
*** DEFINE BASIC ENV VAR
*/

# define TERM "xterm-256color"

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
# define FORWARD_WORD "\033f"//0x06
# define BACKWARD_WORD "\033b"//0x02

/*
*** DEFINE COMMAND CODES
*/

enum					e_one_oct_comm_code
{
	RET_CODE = 0,
	DEL_CODE,
	CPY_MODE_CODE,
	PASTE_CODE,
	FORWARD_CODE,
	BACKWARD_CODE
};

enum					e_multi_oct_comm_code
{
	SUPR_CODE = 10,
	UP_ARROW_CODE,
	DOWN_ARROW_CODE,
	RIGHT_ARROW_CODE,
	LEFT_ARROW_CODE,
	PAGE_UP_CODE,
	PAGE_DOWN_CODE,
	HOME_CODE,
	END_CODE,
	DOWN_LINE_CODE,
	UP_LINE_CODE
};

/*
*** DEFINE STRUCTS
*/

typedef struct s_char   t_char;

struct 					s_char
{
	uint8_t				charac[6];
	size_t				len;
	uint32_t			x_pos;
	int					y_pos;
	int 				is_prompt;
	struct s_char 		*prev;
	struct s_char		*next;
};

typedef struct s_cpy    t_cpy;

struct 					s_cpy
{
	uint8_t				charac[6];
	size_t				len;
	t_cpy				*next;
};

typedef struct 			s_char_list
{
	t_char				*head;
	t_char				*tail;
	uint32_t			char_nb;
}						t_char_list;

typedef void			(*t_key_func)(void);

typedef struct  		s_keymap
{
	char				*seq;
	size_t				len;
	t_key_func			funckey;
}						t_keymap;

typedef struct 				 s_term
{
	struct termios		origin;
	struct termios		capa;
	struct winsize		max;
}						t_term;

struct			s_last_command
{
	uint8_t				*buf;
	int 				last_command_mode;
	t_last_command		*prev;
};

typedef struct 					s_edit
{
	t_char 				*point_char;
	t_char				*mark;
	t_last_command		*last_command;
	t_char_list			char_list;
	t_term				term_info;
	int					reading;
	int					ret_ctrl_c;
	int					edit_mode;
	size_t				cur_base_x;
	int					cur_base_y;
	int 				lines_to_shift;
	uint8_t				*cpy_buff;
}								t_edit;

void					init_signals(void);
void					signal_handler(int signo);
void					modify_term(void);
void					reset_term(void);
void					readline(int prompt_id);
void					readline_errors_controler(int errnum);
void					build_key(uint8_t *key, size_t *keylen, const uint8_t *input);
void					add_char_to_list(uint8_t *charac, size_t len, int is_prompt);
void					delete_char_from_list(t_char *charac);
size_t					get_x_pos(t_char *prev_char, uint32_t col_limit);
size_t					get_y_pos(t_char *prev_char, uint32_t col_limit, uint32_t row_limit);
void					update_all_pos(void);
void					check_all_pos(void);
void					shift_pos_up(void);
void					shift_pos_down(void);
t_char					*skip_prompt(t_char *head);
int						get_buf_size(t_char *head, t_char *end);
uint8_t					*list_to_buff_print(t_char *curr, t_char *end);
void					init_prompt(int prompt_id);
uint8_t 				*prompt_to_buff(t_char_list *list);
void					print_prompt(uint8_t *prompt, size_t prompt_len);
void					clean_screen_from(int x, int y);
void					clean_and_print(void);
void					input_controller(void);
void					move_up(void);
void					move_down(void);
void					move_right(void);
void					move_left(void);
void					go_to_home(void);
void					go_to_end(void);
void					jump_word_forward(void);
void					jump_word_backward(void);
void					exchange_point_mark(void);
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
int						get_word_len(t_char *curr);
void					transpose_word(void);
uint8_t					*build_cpy_buff(t_char *cpy_begin, t_char *cpy_end);
void					copy_current_word(void);
void					copy_all_line(void);
void					paste_copy(void);
void					eot_fn(void);
t_char					*find_first_non_prompt(t_char *head);
void					return_fn(void);
void					free_controler(int code);
void					get_prev_history(void);
void					get_next_history(void);
void					free_all(void);
void					init_prompt(int prompt_id);
void					init_char_list(void);
void					init_edit(void);
void					place_cursor_after_print(t_char *curr, int max_x, int max_y);
void					handle_ctrl_c(void);

#endif
