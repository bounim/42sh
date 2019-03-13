/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:05:15 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/13 16:12:28 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

/*
**	builtin functions header
*/

/*void		built_history(t_rl rl);*/

t_history	*built_exclaim(uint8_t *word, int size, t_history *head); // ????

int			built_cd(char **arg, t_envl **envl);
int			built_echo(char **arg, int *arg_size);
int			built_env(char **arg, t_envl *envl);
int			built_env_find_last_cmd(char **arg);
int			built_setenv_check_error(char **arg);
int			built_setenv(char **arg, t_envl **envl);
int			built_unsetenv(char **arg, t_envl **envl);
int			built_set(t_envl *envl);
int			built_unset(char **arg, t_envl **envl);
int			built_export(char **arg, t_envl **envl);

#endif
