/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <schakor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 10:55:18 by schakor           #+#    #+#             */
/*   Updated: 2019/03/06 15:59:46 by schakor          ###   ########.fr       */
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
	int					history_save;
	int					history_size;
};

t_history			*init_shell_history(void);
void				print_history(void);
void				switch_history(void);
t_history			*rl_new_hist(uint8_t *buf);
t_history			*rl_add_hist(t_history *list, t_history *new_hist);
int					listlen(t_history *list);
#endif