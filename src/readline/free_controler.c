/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_controler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:16:17 by aguillot          #+#    #+#             */
/*   Updated: 2019/03/11 14:43:22 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	free_all_and_exit(void)
{
	t_char *curr;
	t_char *tmp;

	curr = g_shell.edit.char_list.head;
	tmp = NULL;
	if (!curr)
		return ;
	while (curr)
	{
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	if (g_shell.edit.cpy_buff)
		free(g_shell.edit.cpy_buff);
	free_history(g_shell.hist.history);
	exit(0);
}

void	free_only_edit_char_list(void)
{
	t_char *curr;
	t_char *tmp;

	if (!(curr = g_shell.edit.char_list.head))
		return ;
	tmp = NULL;
	while (curr)
	{
		/*printf("\n");
		write(1, curr->charac, curr->len);*/
		tmp = curr->next;
		if (curr)
			free(curr);
		curr = NULL;
		curr = tmp;
	}
	init_char_list();
	g_shell.edit.point_char = NULL;
}

void	free_all_edit(void)
{
	t_char *curr;
	t_char *tmp;

	if (!(curr = g_shell.edit.char_list.head))
		return ;
	tmp = NULL;
	while (curr)
	{
		tmp = curr->next;
		free(curr);
		curr = NULL;
		curr = tmp;
	}
	if (g_shell.edit.cpy_buff)
		free(g_shell.edit.cpy_buff);
}

void	free_controler(int code)
{
	//printf("%d %d %d %d\n", code, FREE_ALL_EDIT, FREE_ALL_AND_EXIT, FREE_ONLY_EDIT_CHAR_LIST);
	if (code == FREE_ALL_AND_EXIT)
		free_all_and_exit();
	if (code == FREE_ALL_EDIT)
		free_all_edit();
	if (code == FREE_ONLY_EDIT_CHAR_LIST)
		free_only_edit_char_list();
}
