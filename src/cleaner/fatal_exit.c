/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatal_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 16:48:23 by schakor           #+#    #+#             */
/*   Updated: 2019/04/22 17:28:15 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void		fatal_exit(int code)
{
	clean_shell();
	if (code == SH_ENOMEM)
		ft_putendl_fd("Cannot allocate memory.", STDERR_FILENO);
	else if (code == SH_EINVAL)
		ft_putendl_fd("Invalid argument.", STDERR_FILENO);
	else if (code == SH_ENOTTY)
		ft_putendl_fd("Inappropriate ioctl device.", STDERR_FILENO);
	else if (code == 6)
		ft_putendl_fd("exit", STDERR_FILENO);
	else if (code == 7)
		ft_putendl_fd("Exec format error", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
