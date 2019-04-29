/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_general_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 11:53:16 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/25 15:31:59 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int				put_error(char *sh, char *cmd, char *arg, char *error)
{
	if (sh)
	{
		ft_putstr_fd(g_shell.progname, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	return (0);
}
