/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:05:15 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/12 16:30:31 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

/*
**	builtin functions header
*/

void		built_history(t_rl rl);
t_history	*built_exclaim(uint8_t *word, int size, t_history *head);
int			built_cd(char **arg, t_envl **env);
int			built_echo(char **arg, int *arg_size);
int			built_env(t_envl *env, char **arg);
int			built_env_check_error(uint8_t **arg, int *arg_size, t_envl *head);
int			built_env_find_last_cmd(char **arg);
int			built_setenv_check_error(uint8_t **arg, int *arg_size);
void		built_setenv();
void		built_unsetenv();

#endif
