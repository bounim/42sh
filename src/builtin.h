/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:05:15 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/19 17:54:49 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

/*
**	builtin functions header
*/

struct					s_opts
{
	int		a;
	int		p;
	int		l;
	int		f;
	int		pp;
	int		t;
	int		i;
};


struct					s_alias
{
	char				*name;
	char				*value;
	struct s_alias		*next;
};

/*void		built_history(t_rl rl);*/

char		*replace_exclaim(char *line, t_history *hist, char *bfr, char *next);
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
int			built_alias(char **arg, t_alias **alias);
int			built_unalias(char **arg, t_alias **alias);
t_alias		*new_alias(char *name, char *value);
void		push_alias(t_alias **alias, char *name, char *value);
t_alias		*addlast_alias(t_alias *head, t_alias *new);
void		print_alias(t_alias *alias);
void		free_alias(t_alias *alias);
int			built_type(char **arg, t_envl **envl);
int			put_error(char *sh, char *cmd, char *arg, char *error);
int			check_opts(char **arg, t_opts *flag, char opts);

#endif
