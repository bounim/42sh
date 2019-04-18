/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_undo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:20:17 by schakor           #+#    #+#             */
/*   Updated: 2019/04/05 19:53:58 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void		vi_undo(void)
{
	delete_last_command(g_shell.edit.last_command);
	undo_last_edit_command();
}

void		vi_undo_all(void)
{
	vi_clear_line_insert();
}
