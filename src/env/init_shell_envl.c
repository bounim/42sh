/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_envl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <schakor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:27:07 by schakor           #+#    #+#             */
/*   Updated: 2019/04/30 19:35:32 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static uint8_t	search_env_var(t_envl *envl, const char *search)
{
	t_envl		*tmp;

	tmp = envl;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, search) == 0)
			return (FOUND);
		tmp = tmp->next;
	}
	return (NOTFOUND);
}

static void		set_env_var(t_envl **envl, const char *name, char *value,
		int opt)
{
	t_envl		*new;

	if (search_env_var(*envl, name) == NOTFOUND)
	{
		if (!(new = (t_envl *)malloc(sizeof(*new))))
			fatal_exit(SH_ENOMEM);
		new->name = ft_strdup(name);
		new->read_only = (opt & ENV_RO) == ENV_RO;
		new->value = value;
		new->exp = (opt & ENV_EX) == ENV_EX;
		new->next = NULL;
		*envl = addlast_envl(*envl, new);
	}
	else
		free(value);
}

static void		init_new_env(t_envl *new, char *env, char *ptr)
{
	new->name = ft_strsub(env, 0, ptr - env);
	new->value = ft_strsub(env, (uint32_t)(ptr - env + 1), ft_strlen(ptr));
	new->exp = 1;
	new->read_only = 0;
	new->next = NULL;
	if (ft_strcmp(new->name, "SHLVL") == 0)
	{
		ptr = ft_itoa(ft_atoi(new->value) + 1);
		free(new->value);
		new->value = ptr;
	}
}

t_envl			*envarr_to_envl(char **env)
{
	t_envl		*ret;
	t_envl		*new;
	char		*ptr;

	ret = NULL;
	if (!env)
		return (ret);
	while (*env != NULL)
	{
		if ((ptr = ft_strchr(*env, '=')))
		{
			if (!(new = (t_envl *)malloc(sizeof(*new))))
				return (NULL);
			init_new_env(new, *env, ptr);
			ret = addlast_envl(ret, new);
		}
		env++;
	}
	return (ret);
}

t_envl			*init_shell_envl(char **env)
{
	t_envl		*ret;
	t_passwd	*pwuid;
	char		cwd[PATH_MAX + 1];

	ret = envarr_to_envl(env);
	if ((pwuid = getpwnam(getlogin())) == NULL)
		fatal_exit(SH_ENOMEM);
	if (getcwd(cwd, PATH_MAX) == NULL)
		fatal_exit(SH_ENOMEM);
	set_env_var(&ret, "HOME", ft_strjoin("/Users/", pwuid->pw_name), ENV_EX);
	set_env_var(&ret, "LOGNAME", ft_strdup(pwuid->pw_name), ENV_RO | ENV_EX);
	set_env_var(&ret, "SHLVL", ft_strdup("1"), ENV_EX);
	set_env_var(&ret, "PWD", ft_strdup(cwd), ENV_EX);
	set_env_var(&ret, "OLDPWD", ft_strdup(cwd), ENV_EX);
	set_env_var(&ret, "HISTFILE", ft_strjoin(get_env_val(ret, "HOME"),
				"/.21sh_history"), ENV_EX);
	set_env_var(&ret, "HISTSIZE", ft_strdup("50000"), ENV_EX);
	return (ret);
}
