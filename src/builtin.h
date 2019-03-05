/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:05:15 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/04 17:25:05 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

/*
**	builtin functions header
*/

void		built_history(t_rl rl);
t_history	*built_exclaim(uint8_t *word, int size, t_history *head);
void		built_cd();
int			built_echo(uint8_t **arg, int *arg_size);
int			built_env(t_envl *head, uint8_t **arg, int *arg_size, int last_cmd, int curr_arg);
int			built_env_check_error(uint8_t **arg, int *arg_size, t_envl *head);
int			built_env_find_last_cmd(uint8_t **arg, int *arg_size);
int			built_setenv_check_error(uint8_t **arg, int *arg_size);
void		built_setenv();
void		built_unsetenv();

#endif
