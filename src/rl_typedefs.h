/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_typedefs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:40:01 by schakor           #+#    #+#             */
/*   Updated: 2019/03/06 15:59:46 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RL_TYPEDEFS_H
# define RL_TYPEDEFS_H

typedef struct s_rl				t_rl;
typedef struct s_keymapi		t_keymapi;
typedef struct s_bufvar			t_bufvar;
typedef void	(*t_rl_command_func)(t_rl *rl);
typedef struct s_history		t_history;

#endif
