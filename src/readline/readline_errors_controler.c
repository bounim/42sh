/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_errors_controler.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 15:57:49 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/02 18:37:00 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void	print_usage(void)
{
	ft_putstr("usage: line_editing\n");
	ft_putstr("a prompt will appear, than you can edit line\n");
}

void		readline_errors_controler(int errnum)
{
	if (errnum == PRINT_USAGE)
		print_usage();
	else if (errnum == NO_TERM_ENV)
		ft_putstr("Can't find env variable TERM. Exit..\n");
	else if (errnum == NO_TERM_INFO)
		ft_putstr("Can't retreive term info. Exit\n");
	else if (errnum == MALLOC_ERROR)
		ft_putstr("Malloc error\n");
	else if (errnum == EXIT)
		ft_putstr("Exit(0)\n");
	rl_free_controler(FREE_ALL_AND_EXIT);
	cooked_terminal();
	exit(1);
}
