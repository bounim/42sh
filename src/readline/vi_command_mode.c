/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_command_mode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:20:17 by schakor           #+#    #+#             */
/*   Updated: 2019/04/05 19:53:58 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void			vi_command_mode(void)
{
	move_left();
	g_shell.edit.edit_mode = MODE_VI_COMMAND;
}

void			invoke_vi(void)
{
	return ;
}

static t_char	*find_last_prompt(t_char *head)
{
	t_char		*ret;

	ret = head;
	while (ret->next && ret->is_prompt == 1)
	{
		if (ret->next->is_prompt == 0)
			break ;
		ret = ret->next;
	}
	return (ret);
}

static t_char	*new_char_comment(void)
{
	t_char		*new;

	if (!(new = (t_char *)malloc(sizeof(*new))))
		fatal_exit(SH_ENOMEM);
	ft_memset(new->charac, '\0', sizeof(new->charac));
	new->charac[0] = '#';
	new->len = 1;
	new->is_prompt = 0;
	return (new);
}

void			treat_as_comment(void)
{
	t_char		*last_prompt;
	t_char		*new;
	t_char		*next;

	last_prompt = find_last_prompt(g_shell.edit.char_list.head);
	new = new_char_comment();
	if (!last_prompt->next)
	{
		last_prompt->next = new;
		new->prev = last_prompt;
		new->next = NULL;
		g_shell.edit.char_list.tail = new;
	}
	else
	{
		next = last_prompt->next;
		last_prompt->next = new;
		new->prev = last_prompt;
		new->next = next;
		next->prev = new;
	}
	update_all_pos();
	clean_and_print();
	return_fn();
}
