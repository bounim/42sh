/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:18:52 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/08 13:44:43 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int		check_builtin(char *cmd)
{
	return (cmd && (ft_strequ(cmd, "alias")
			|| ft_strequ(cmd, "bg") || ft_strequ(cmd, "fg")
			|| ft_strequ(cmd, "cd") || ft_strequ(cmd, "debug")
			|| ft_strequ(cmd, "echo") || ft_strequ(cmd, "env")
			|| ft_strequ(cmd, "exit") || ft_strequ(cmd, "export")
			|| ft_strequ(cmd, "history") || ft_strequ(cmd, "jobs")
			|| ft_strequ(cmd, "set") || ft_strequ(cmd, "setenv")
			|| ft_strequ(cmd, "type") || ft_strequ(cmd, "unalias")
			|| ft_strequ(cmd, "unset") || ft_strequ(cmd, "unsetenv")));
}
