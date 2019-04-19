/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_envl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <schakor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:27:07 by schakor           #+#    #+#             */
/*   Updated: 2019/04/15 14:58:12 by aguillot         ###   ########.fr       */
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

static void		set_env_var(t_envl **envl, const char *name, char *value,\
		size_t read)
{
	t_envl		*new;

	if (search_env_var(*envl, name) == NOTFOUND)
	{
		if (!(new = (t_envl *)malloc(sizeof(*new))))
			fatal_exit(SH_ENOMEM);
		new->name = ft_strdup(name);
		new->read_only = read;
		new->value = value;
		new->exp = 1;
		new->next = NULL;
		*envl = addlast_envl(*envl, new);
	}
}

static void		set_env_var_unexp(t_envl **envl, const char *name, char *value,\
		size_t read)
{
	t_envl		*new;

	if (search_env_var(*envl, name) == NOTFOUND)
	{
		if (!(new = (t_envl *)malloc(sizeof(*new))))
			fatal_exit(SH_ENOMEM);
		new->name = ft_strdup(name);
		new->read_only = read;
		new->value = value;
		new->exp = 0;
		new->next = NULL;
		*envl = addlast_envl(*envl, new);
	}
}

static void		set_envl_default_value(t_envl **envl)
{
	t_passwd	*pwuid;
	char		*cwd;

	if ((pwuid = getpwnam(getlogin())) == NULL)
		fatal_exit(SH_ENOMEM);
	if ((cwd = getcwd(NULL, 0)) == NULL)
		fatal_exit(SH_ENOMEM);
	set_env_var(envl, "HOME", ft_strjoin("/Users/", pwuid->pw_name), 0);
	set_env_var(envl, "LOGNAME", ft_strdup(pwuid->pw_name), 1);
	set_env_var(envl, "SHLVL", ft_strdup("1"), 0);
	set_env_var(envl, "PWD", ft_strdup(cwd), 0);
	set_env_var(envl, "OLDPWD", ft_strdup(cwd), 0);
//	set_env_var_unexp(envl, "42SH_ARGC", ft_itoa(g_shell.argc), 1);
//	set_env_var_unexp(envl, "42SH_ARGV", ft_arrdup(g_shell.argv), 1);
	set_env_var_unexp(envl, "HISTFILE", ft_strjoin(get_env_val(*envl, "HOME"),\
				"/.42sh_history"), 0);
	set_env_var_unexp(envl, "HISTSIZE", ft_strdup("50000"), 0);
	set_env_var_unexp(envl, "$", NULL, 2);
	set_env_var_unexp(envl, "?", NULL, 2);
	set_env_var_unexp(envl, "0", NULL, 2);
}

static t_envl	*envarr_to_envl(char **env)
{
	t_envl		*ret;
	t_envl		*new;
	char		*ptr;

	ret = NULL;
	if (!env)
		return (ret);
	while (*env != NULL)
	{
		if (!(new = (t_envl *)malloc(sizeof(*new))))
			return (NULL);
		ptr = ft_strchr(*env, '=');
		new->name = ft_strsub(*env, 0, ptr - *env);
		new->value = ft_strsub(*env, ptr - *env + 1, ft_strlen(ptr));
		new->exp = 1;
		new->read_only = 0;
		new->next = NULL;
		if (ft_strcmp(new->name, "SHLVL") == 0)
		{
			ptr = ft_itoa(ft_atoi(new->value) + 1);
			free(new->value);
			new->value = ptr;
		}
		ret = addlast_envl(ret, new);
		env++;
	}
	return (ret);
}

t_envl			*init_shell_envl(char **env)
{
	t_envl		*ret;

	ret = envarr_to_envl(env);
	set_envl_default_value(&ret);
	return (ret);
}
