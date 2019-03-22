/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_last_editing_command.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <schakor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 15:35:04 by schakor           #+#    #+#             */
/*   Updated: 2019/03/21 18:17:57 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

/*
**  Undo last editing command using linked list :
**
**  if last command is insertion, then delete the characters inserted in the
**  last command. if last command is deletion, then insert the characters
 * 	deleted in the last command.
*/

static void		delete_last_characters_inserted(void)
{
	return ;
}

static void		insert_last_characters_deleted(void)
{
 	return ;
}

t_last_command	*addlast_last_command(t_last_command *head, t_last_command *new)
{
	t_last_command	*tmp;

	if (head == NULL)
		return (new);
	else if (new == NULL)
		return (head);
	tmp = head;
	while (tmp->prev != NULL)
		tmp = tmp->prev;
	tmp->prev = new;
	return (head);
}

void				add_char_last_command(const uint8_t *buf, int last_command_mode)
{
	t_last_command	*new;

	if (!(new = (t_last_command *)malloc(sizeof(*new))))
		fatal_exit(SH_ENOMEM);
	new->buf = ft_u8_strdup(buf);
	new->last_command_mode = last_command_mode;
	g_shell.edit.last_command = addlast_last_command(g_shell.edit.last_command, new);
}

void			undo_last_editing_command(void)
{
	if (g_shell.edit.last_command->last_command_mode == INSERT_MODE)
		delete_last_characters_inserted();
	else if (g_shell.edit.last_command->last_command_mode == DELETE_MODE)
		insert_last_characters_deleted();
}