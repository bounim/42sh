/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_job2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 05:54:30 by emartine          #+#    #+#             */
/*   Updated: 2019/05/07 05:54:31 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"
#include "execution.h"
#include "lexer/lexer_internal.h"

static int		add_job_loop(t_job **prev, t_job **cur, t_job *new)
{
	while ((*cur)->next)
	{
		if ((*prev ? (*prev)->jobspec + 1 : 1) < (*cur)->jobspec)
		{
			if (*prev)
				(*prev)->next = new;
			else
				g_shell.head_job = new;
			new->jobspec = (*prev ? (*prev)->jobspec + 1 : 1);
			new->next = *cur;
			if (!new->background)
			{
				g_shell.previous_job = g_shell.current_job;
				g_shell.current_job = new;
			}
			return (-1);
		}
		*prev = *cur;
		*cur = (*cur)->next;
	}
	return (0);
}

void			add_job(t_job *new)
{
	t_job *prev;
	t_job *cur;

	if (!new || new->jobspec > 0)
		return ;
	if (!g_shell.head_job)
	{
		g_shell.head_job = new;
		new->jobspec = 1;
		g_shell.current_job = new;
		return ;
	}
	prev = NULL;
	cur = g_shell.head_job;
	if (add_job_loop(&prev, &cur, new) < 0)
		return ;
	cur->next = new;
	new->jobspec = cur->jobspec + 1;
	if (!new->background)
	{
		g_shell.previous_job = g_shell.current_job;
		g_shell.current_job = new;
	}
}

t_proc			*create_proc_argv(t_job **job, char path[PATH_MAX + 1],
		char **argv, t_envl *envl)
{
	t_proc	*new;

	if (!*job && !(*job = create_job_argv(argv)))
		return (NULL);
	if (!(new = init_proc()))
		return (NULL);
	new->arg = ft_arrdup(argv);
	new->envl = dup_envl(envl ? envl : g_shell.envl);
	ft_memmove(new->path, path, PATH_MAX + 1);
	return (add_proc_list(*job, new));
}

static int		create_background_job_parent(t_lexer_token *amp, pid_t pid)
{
	t_job	*job;
	t_proc	*proc;

	if (!(job = create_job(NULL)))
		return (-1);
	if (!(proc = init_proc()))
	{
		free_job(job);
		return (-1);
	}
	add_job(job);
	add_proc_list(job, proc);
	job->pgid = pid;
	job->cmd = lst_to_str(amp, 1);
	job->background = 1;
	job->running = 1;
	proc->pid = pid;
	printer_char(&g_shell.err, '[');
	printer_ulong(&g_shell.err, job->jobspec);
	printer_bin(&g_shell.err, (uint8_t *)"] ", 2);
	printer_ulong(&g_shell.err, (size_t)pid);
	printer_endl(&g_shell.err);
	printer_flush(&g_shell.err);
	return (1);
}

int				create_background_job(t_lexer_token *amp)
{
	pid_t	pid;

	if ((pid = fork()) < 0)
		fatal_exit(SH_ENOMEM);
	if (pid > 0)
		return (create_background_job_parent(amp, pid));
	signal(SIGINT, SIG_IGN);
	signal(SIGWINCH, SIG_IGN);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGSTOP, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	free_exec();
	g_shell.background = 1;
	g_shell.pgid = getpid();
	setpgid(0, g_shell.pgid);
	return (0);
}
