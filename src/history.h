/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <schakor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 10:55:18 by schakor           #+#    #+#             */
/*   Updated: 2019/03/19 13:56:03 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H


struct					s_history
{
	uint8_t					*buf;
	size_t					len;
	t_history				*next;
	t_history				*bfr;
};

struct					s_hist
{
	t_history			*history;
	uint8_t				*buf;
	int					history_save;
	int					history_size;
};

t_history			*init_shell_history(void);
void				print_history(void);
void				switch_history(void);
t_history			*rl_new_hist(uint8_t *buf);
t_history			*rl_add_hist(t_history *list, t_history *new_hist);
int					listlen(t_history *list);
uint8_t				*list_to_buf(void);
void				buff_to_charlist(uint8_t *buf);
void				search_in_history(void);
void				del_charac_in_search(void);
void				execute_search_command(void);
void				give_up_search(void);
void				back_to_readline(void);
void				find_in_history(uint8_t	*buff, size_t *len);
#endif