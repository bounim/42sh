/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing_errors_controler.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:19:08 by aguillot          #+#    #+#             */
/*   Updated: 2019/03/06 18:40:06 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void	print_usage(void)
{
	ft_putstr("usage: line_editing\n");
	ft_putstr("a prompt will appear, than you can edit line\n");
}

void		line_editing_errors_controler(int errnum)
{
	if (errnum == PRINT_USAGE)
		print_usage();
	else if (errnum == NO_TERM_ENV)
		ft_putstr("Can't find env variable TERM. Exit..\n");
	else if (errnum == NO_TERM_INFO)
		ft_putstr("Can't retreive term info. Exit\n");
	else if (errnum == MALLOC_ERROR)
		ft_putstr("Malloc error\n");
	//free_shit();
	cooked_terminal();
	exit(1);
}
