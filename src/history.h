/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <schakor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 10:55:18 by schakor           #+#    #+#             */
/*   Updated: 2019/04/24 13:17:28 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

struct				s_history
{
	uint8_t			*buf;
	size_t			len;
	t_history		*next;
	t_history		*bfr;
};

struct				s_hist
{
	t_history		*history;
	uint8_t			search_buff[15000];
	size_t			search_len;
	int				history_save;
	int				history_size;
	int				unicode_err;
};

typedef void		(*t_search_func)(void);

typedef struct		s_searchmap
{
	char			*seq;
	size_t			len;
	t_search_func	searchfunc;
}					t_searchmap;

t_history			*init_shell_history(void);
void				update_base_y_in_search(uint8_t *buff, int i);
void				print_history(void);
void				switch_history(void);
t_history			*find_first_hist_line(void);
t_history			*find_last_hist_line(void);
t_history			*find_specific_hist_line(int line, t_history *head);
t_history			*rl_new_hist(uint8_t *buf);
t_history			*rl_add_hist(t_history *list, t_history *new_hist);
int					get_hist_full_size(t_history *tail);
int					listlen(t_history *list);
uint8_t				*list_to_buf(void);
void				buff_to_charlist(uint8_t *buf);
void				search_in_history(void);
void				del_charac_in_search(void);
void				execute_search_command(void);
void				give_up_search(void);
void				get_prev_history(void);
void				get_next_history(void);
void				back_to_readline(void);
int					find_in_history(int save);
t_history			*find_specific_hist_line(int line, t_history *head);
void				file_from_history(t_history *hist);
void				print_historyl(t_history *hist);
void				resize_history(t_history *hist);
void				free_history(t_history *hist);
void				print_search_prompt(void);
void				print_search_result(t_history *curr);
void				build_search_buff(uint8_t *key, size_t *keylen);
void				check_nul_charac(uint8_t buf[BUFF_SIZE + 1], ssize_t rd);
void				rl_line_to_hist(int add_to_hist, uint8_t *buff);

#endif
