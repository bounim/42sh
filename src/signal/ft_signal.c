/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 14:13:02 by khsadira          #+#    #+#             */
/*   Updated: 2019/02/19 12:06:55 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	ft_sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		signal(SIGINT, ft_sig_handler);
	}
}

void	ft_signal(int signo)
{
	if (signo == SIGINT)
	{
		cooked_terminal();
		ft_putstr("\n");
	}
	else if (signo == SIGSEGV)
	{
		cooked_terminal();
		ft_putstr("\n");
		ft_putendl_fd("Khan please fix the segfault, thanks.", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	else if (signo == SIGABRT)
	{
		cooked_terminal();
		ft_putstr("\n");
		ft_putendl_fd("Khan , why does the program abort ?", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}
