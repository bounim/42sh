/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:52:10 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/26 14:57:41 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int			env_exit(char *str, int test)
{
	ft_putstr_fd(g_shell.progname, 2);
	ft_putstr_fd(": env: ", 2);
	ft_putstr_fd(str, 2);
	if (test < 0 || test == 1)
	{
		ft_putendl_fd(": No such file or directory", 2);
		exit(127);
	}
	ft_putendl_fd(": Operation not permitted", 2);
	exit(126);
}

int			env_usage(char *str, t_envl *head)
{
	free_envl(head);
	printer_str(&g_shell.err, "env: illegal option -- ");
	printer_char(&g_shell.err, *(str + 1));
	printer_str(&g_shell.err, "\nusage: env [-i] [name=value ...]");
	printer_str(&g_shell.err, " [utility [argument ...]]");
	printer_endl(&g_shell.err);
	printer_flush(&g_shell.err);
	return (125);
}

char		**from_arg_to_cmd(char **start)
{
	char	**ret;
	int		i;

	i = 0;
	ret = NULL;
	while (start[i])
		i++;
	if (!(ret = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	ret[i] = NULL;
	i = 0;
	while (start[i])
	{
		ret[i] = ft_strdup(start[i]);
		i++;
	}
	return (ret);
}

int			is_valid_name(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] && ft_isdigit(str[i]))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void		init_cor(char **arg, t_envl *envl, t_cor *cor)
{
	cor->t = arg + 1;
	cor->dup_env = dup_envl(envl);
	cor->name = NULL;
	cor->start = NULL;
	cor->o = 1;
}
