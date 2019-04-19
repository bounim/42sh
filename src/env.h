/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 13:07:26 by schakor           #+#    #+#             */
/*   Updated: 2019/04/03 09:45:46 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

/*
**	environment functions header
*/

struct					s_envl
{
	char				*name;
	char				*value;
	size_t				exp;
	size_t				read_only;
	struct s_envl		*next;
};

void					print_envl(t_envl *env, int exp);
void					free_envl(t_envl *env);
t_envl					*init_shell_envl(char **env);
t_envl					*addlast_envl(t_envl *head, t_envl *new);
char					*get_env_val(t_envl *envl, char *name);
void					push_env(t_envl **envl, char *name, char *value,
		int exp);
void					clear_envl(t_envl *envl);
t_envl					*dup_envl(t_envl *env);
char					**envl_to_envarr(t_envl *envl);
t_envl					*envarr_to_envl(char **env);

# define ENV_EX (1 << 0)
# define ENV_RO (1 << 1)

#endif
