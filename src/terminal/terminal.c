/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 16:01:24 by schakor           #+#    #+#             */
/*   Updated: 2019/03/06 15:59:46 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

/*
** function to switch terminal in raw mode (non-canonical terminal)
*/

void			raw_terminal(void)
{
	if (g_shell.term_set == TERM_SET)
	{
		if (tcsetattr(STDIN_FILENO, TCSADRAIN, &(g_shell.raw_tio)))
		{
			perror(""); //FIXMESENPAII
			fatal_exit(SH_EINVAL);
		}
	}
}

/*
** function to switch terminal in cooked mode (canonical terminal)
*/

void			cooked_terminal(void)
{
	if (g_shell.term_set == TERM_SET)
	{
		if (tcsetattr(STDIN_FILENO, TCSANOW, &(g_shell.cooked_tio)))
		{
			perror("");//FIXME
			fatal_exit(SH_ENOMEM);
		}
	}
}
