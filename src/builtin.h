/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:05:15 by khsadira          #+#    #+#             */
/*   Updated: 2019/05/07 03:50:59 by khsadira         ###   ########.fr       */
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

enum		e_fc_opts
{
	E = 0,
	L = 1,
	N = 2,
	R = 3,
	S = 4
};

enum		e_fc_code
{
	IN_RANGE = 0,
	OUT_OF_RANGE = 1,
	NO_ARG = 2,
	CMD_NOT_FOUND = 3 
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
int					built_fc(char **av, t_envl *envl);
int					check_fc_opts(char **av, int fc_opts[5]);
int					build_fc_range(char **av, int fc_range[2], int fc_otps[5]);
void				manage_fc_l(int fc_opts[5], int fc_range[5]);
void				print_usage_fc(char opt);
int					fc_s(uint8_t **buff, int len);
int 				fc_modification(uint8_t **buff, t_envl *envl, char *editor, int len);
int					check_fc_range(int fc_range[2]);
int					return_fc_error(int fc_err_code, char *av);
int					check_if_arg_isdigit(char **av);
int 				get_good_value_for_range(int value, int histsize);
char				*replace_alias(char *line, t_alias *alias, int i, int n);
char				*manage_alias_buff(char *buff, t_alias *alias, int *i, int *n);
char				*find_alias(char *word, t_alias *alias, t_alias *lnk_alias, int *lnk);
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
int					built_jobs(char **arg, t_envl *envl);
int					built_fg(char **arg, t_envl *envl);
int					built_bg(char **arg, t_envl *envl);
t_job				*built_bg_fg_job(char **arg);
void				detailed_list(t_printer *pr, t_job *job, int show_pgid,
		int exit_code);

#endif
