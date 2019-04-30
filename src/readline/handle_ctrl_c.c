/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ctrl_c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <schakor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 19:12:19 by schakor           #+#    #+#             */
/*   Updated: 2019/03/12 19:14:21 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void		handle_ctrl_c(void)
{
	write(1, "\n", 1);
	rl_free_controler(FREE_ONLY_EDIT_CHAR_LIST);
	free_last_command_list();
	g_shell.edit.reading = FALSE;
	g_shell.edit.ret_ctrl_c = TRUE;
}
