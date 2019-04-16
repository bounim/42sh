/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 15:23:17 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/05 15:23:19 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	init_ptr_func(int (*func[19])(char **arg, t_envl *envl))
{
	func[0] = built_cd;
	func[1] = built_echo;
	func[2] = built_env;
	func[3] = built_setenv;
	func[4] = built_unsetenv;
	func[5] = built_set;
	func[6] = built_unset;
	func[7] = built_export;
	func[8] = built_alias;
	func[9] = built_unalias;
	func[10] = built_history;
	func[11] = built_fg;
	func[12] = built_bg;
	func[13] = built_jobs;
	func[14] = built_type;
	func[15] = built_debug;
	func[16] = built_exit;
	func[17] = built_fc;
	func[18] = NULL;
	return (0);
}

static int	init_ptr_cmd(char *cmd[19])
{
	cmd[0] = "cd";
	cmd[1] = "echo";
	cmd[2] = "env";
	cmd[3] = "setenv";
	cmd[4] = "unsetenv";
	cmd[5] = "set";
	cmd[6] = "unset";
	cmd[7] = "export";
	cmd[8] = "alias";
	cmd[9] = "unalias";
	cmd[10] = "history";
	cmd[11] = "fg";
	cmd[12] = "bg";
	cmd[13] = "jobs";
	cmd[14] = "type";
	cmd[15] = "debug";
	cmd[16] = "exit";
	cmd[17] = "fc";
	cmd[18] = NULL;
	return (0);
}

int			start_builtin(char **arg, t_envl *envl)
{
	char	*cmd[19];
	int		(*func[19])(char **arg, t_envl *envl);
	int		i;
	int		ret;

	if (!arg || !arg[0])
		return (-1);
	init_ptr_cmd(cmd);
	init_ptr_func(func);
	i = 0;
	while (cmd[i])
	{
		if (ft_strequ(cmd[i], arg[0]))
		{
			ret = func[i](arg, envl);
			return (ret);
		}
		i++;
	}
	return (-1);
}