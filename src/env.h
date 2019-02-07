/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 13:07:26 by schakor           #+#    #+#             */
/*   Updated: 2019/02/06 14:23:54 by schakor          ###   ########.fr       */
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
	struct s_envl		*next;
};

t_envl					*addlast_envl(t_envl *head, t_envl *new);
t_envl					*envarr_2_envl(char **env);
char					*get_env_val(t_envl *envl, char *name);
void					push_env(t_envl **envl, char *name, char *value);
void					clear_envl(t_envl *envl);

#endif
