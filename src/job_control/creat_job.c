/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:38:54 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/04 13:56:23 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	creat_job(char *cmd)
{
	t_job	*new;

	if (!(new = init_job(new)))
		return (NULL);
	new->cmd = ft_strdup(cmd);
	return (new);
}

t_proc	*creat_proc(char **arg, t_envl *envl, char *path)
{
	t_proc	*new;

	if (!(new = init_proc(new)))
		return (NULL);
	proc->arg = ft_arrdup(arg);
	proc->env = envl_to_arr(envl);
	proc->path = ft_strdup(path);
	return (new);
}

t_job	*add_job(t_job *head, t_job *new)
{
	t_job	*tmp;

	if (!head)
		return (new);
	else if (!new)
		return (head);
	tmp = head;
	while (tmp)
		tmp = tmp->next;
	tmp->next = new;
	return (head);
}

void	add_proc(t_proc *head, t_proc *new)
{
	t_proc	*tmp;

	if (!head)
		return (new);
	else if (!new)
		return (head);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (head);
}
