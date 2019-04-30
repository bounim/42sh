/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:05:15 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/22 16:28:23 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

/*
**	builtin functions header
*/

struct				s_opts
{
	int				a;
	int				p;
	int				l;
	int				f;
	int				pp;
	int				t;
	int				i;
};

struct				s_opt_jobs
{
	int				l;
	int				p;
};

struct				s_alias
{
	char			*name;
	char			*value;
	struct s_alias	*next;
};

typedef struct		s_builtin
{
	char			*name;
	int				(*func)(char **, t_envl *);
}					t_builtin;

typedef struct		s_cor
{
	t_envl			*dup_env;
	char			**t;
	char			**start;
	int				o;
	char			*name;
}					t_cor;

int					check_builtin(char *cmd);
int					start_builtin(char **arg, t_envl *envl);
char				**from_arg_to_cmd(char **start);
int					env_exit(char *str, int test);
int					env_usage(char *str, t_envl *envl);
void				init_cor(char **arg, t_envl *envl, t_cor *cor);
int					built_alias(char **arg, t_envl *envl);
int					built_cd(char **arg, t_envl *envl);
char				*find_cdpath(char *arg, t_envl *envl, int opts);
char				*rework_cdpath_arr(char *cdpath);
int					built_debug(char **arg, t_envl *envl);
int					built_echo(char **arg, t_envl *envl);
int					built_env(char **arg, t_envl *envl);
int					is_valid_name(char *str);
int					built_exit(char **arg, t_envl *envl);
int					built_export(char **arg, t_envl *envl);
int					built_hash(char **arg, t_envl *envl);
int					built_history(char **arg, t_envl *envl);
int					built_set(char **arg, t_envl *envl);
int					built_setenv(char **arg, t_envl *envl);
int					built_setenv_check_error(char **arg);
int					built_test(char **av, t_envl *envl);
int					built_type(char **arg, t_envl *envl);
int					built_unalias(char **arg, t_envl *envl);
int					built_unset(char **arg, t_envl *envl);
int					built_unsetenv(char **arg, t_envl *envl);

int					built_env_find_last_cmd(char **arg, int stock, int i);
char				*replace_exclaim(char *line, t_history *hist, char *bfr,
		char *next);
char				*find_exclaim(char *word, t_history *hist);
char				*rework_canonic_path(char *cwd);
int					cd_first_arg(char **arg, int *opts);
int					unary_test(char *cmd, char *operator, char *operand);
int					binary_test(char *cmd, char *operand1, char *operator,
		char *operand2);
int					unexpected(char *cmd, char *arg, char *reason);
int					check_opts_jobs(char **arg, t_opt_jobs *jobs);
t_alias				*new_alias(char *name, char *value);
void				push_alias(t_alias **alias, char *name, char *value);
t_alias				*addlast_alias(t_alias *head, t_alias *new);
int					print_alias(t_alias *alias);
int					free_alias(t_alias *alias, int a);
int					put_error(char *sh, char *cmd, char *arg, char *error);
int					check_opts(char **arg, t_opts *flag, char opts);

#endif
