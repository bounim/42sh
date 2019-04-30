/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_assign.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 16:32:02 by kberisha          #+#    #+#             */
/*   Updated: 2019/04/09 17:04:53 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"
#include "execution.h"

static int	execute_assign(t_lexer_token *cmd, t_proc *proc,
		t_lexer_token *assign)
{
	char	*name;
	char	*value;

	if (NULL == (name = malloc(assign->assign_position + 1)))
		return (-1);
	if (NULL == (value = malloc(assign->size - assign->assign_position)))
	{
		free(name);
		return (-1);
	}
	ft_memcpy(name, assign->buffer, assign->assign_position);
	name[assign->assign_position] = '\0';
	ft_memcpy(value, assign->buffer + assign->assign_position + 1,
			assign->size - assign->assign_position - 1);
	value[assign->size - assign->assign_position - 1] = '\0';
	if (cmd->arg_head)
		push_env(&proc->envl, name, value, 1);
	else
		push_env(&g_shell.envl, name, value, 0);
	free(name);
	free(value);
	return (0);
}

int			execute_assign_list(t_lexer_token *cmd, t_proc *proc)
{
	t_lexer_token *tmp;

	tmp = cmd->assign_head;
	while (tmp)
	{
		if (execute_assign(cmd, proc, tmp) < 0)
			return (-1);
		tmp = tmp->assign_next;
	}
	return (0);
}
