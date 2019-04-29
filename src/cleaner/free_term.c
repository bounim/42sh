/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 21:45:10 by schakor           #+#    #+#             */
/*   Updated: 2019/04/22 17:27:52 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void			clean_shell(void)
{
	t_history *curr;

	curr = find_last_hist_line();
	free_envl(g_shell.envl);
	free_history(curr);
	rl_free_controler(FREE_ALL_EDIT);
	hashmap_clean(&g_shell.hmap);
	lexer_destroy(g_shell.lexer);
	free(g_shell.line);
	free(g_shell.canonic_path);
	free_exec();
}
