/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_typedefs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:40:01 by schakor           #+#    #+#             */
/*   Updated: 2018/12/17 18:32:38 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RL_TYPEDEFS_H
# define RL_TYPEDEFS_H

typedef struct s_rl				t_rl;
typedef struct s_keymap			t_keymap;
typedef struct s_bufvar			t_bufvar;
typedef void	(*t_rl_command_func)(t_rl *rl);
typedef struct s_history		t_history;

#endif
