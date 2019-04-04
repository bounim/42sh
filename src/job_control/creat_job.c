/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:38:54 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/04 14:40:58 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

t_job	*creat_job(char *cmd)
{
	t_job	*new;

	new = NULL;
	if (!(new = init_job(new)))
		return (NULL);
	new->cmd = ft_strdup(cmd);
	return (new);
}

t_proc	*creat_proc(char **arg, t_envl *envl, char *path)
{
	t_proc	*new;

	new = NULL;
	if (!(new = init_proc(new)))
		return (NULL);
	new->arg = ft_arrdup(arg);
	new->env = envl_to_envarr(envl);
	new->path = ft_strdup(path);
	return (new);
}

t_job	*add_job(t_job *head, t_job *new_job)
{
	t_job	*tmp;

	if (!head)
		return (new_job);
	else if (!new_job)
		return (head);
	tmp = head;
	while (tmp)
		tmp = tmp->next;
	tmp->next = new_job;
	return (head);
}

t_proc	*add_proc(t_proc *head, t_proc *new_proc)
{
	t_proc	*tmp;

	if (!head)
		return (new_proc);
	else if (!new_proc)
		return (head);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_proc;
	return (head);
}