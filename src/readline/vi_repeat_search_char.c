/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_repeat_search_char.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 11:49:35 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/11 11:49:37 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	repeat_last_search_char(void)
{
	if (g_shell.edit.vi_last_search_fn == SEARCH_CHAR_AFTER)
		vi_repeat_after(g_shell.edit.vi_last_search_char);
	else if (g_shell.edit.vi_last_search_fn == SEARCH_CHAR_BEFORE)
		vi_repeat_before(g_shell.edit.vi_last_search_char);
	else if (g_shell.edit.vi_last_search_fn == SEARCH_CHAR_AFTER_BEFORE)
		vi_repeat_after_before(g_shell.edit.vi_last_search_char);
	else if (g_shell.edit.vi_last_search_fn == SEARCH_CHAR_BEFORE_AFTER)
		vi_repeat_before_after(g_shell.edit.vi_last_search_char);
}

void	repeat_last_search_char_reverse(void)
{
	if (g_shell.edit.vi_last_search_fn == SEARCH_CHAR_AFTER)
		vi_repeat_before(g_shell.edit.vi_last_search_char);
	else if (g_shell.edit.vi_last_search_fn == SEARCH_CHAR_BEFORE)
		vi_repeat_after(g_shell.edit.vi_last_search_char);
	else if (g_shell.edit.vi_last_search_fn == SEARCH_CHAR_AFTER_BEFORE)
		vi_repeat_before_after(g_shell.edit.vi_last_search_char);
	else if (g_shell.edit.vi_last_search_fn == SEARCH_CHAR_BEFORE_AFTER)
		vi_repeat_after_before(g_shell.edit.vi_last_search_char);
}
