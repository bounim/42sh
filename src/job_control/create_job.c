/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:38:54 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/10 18:56:26 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"
#include "execution.h"
#include "lexer/lexer_internal.h"

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
	while (cur->next)
	{
		if ((prev ? prev->jobspec + 1 : 1) < cur->jobspec)
		{
			if (prev)
			{
				prev->next = new;
				new->jobspec = prev->jobspec + 1;
			}
			else
			{
				g_shell.head_job = new;
				new->jobspec = 1;
			}
			new->next = cur;
			if (!new->background /*&& !new->stopped*/)
			{
				g_shell.previous_job = g_shell.current_job;
				g_shell.current_job = new;
			}
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
	cur->next = new;
	new->jobspec = cur->jobspec + 1;
	if (!new->background /*&& !new->stopped*/)
	{
		g_shell.previous_job = g_shell.current_job;
		g_shell.current_job = new;
	}
}

static t_job	*create_job(t_lexer_token *cmd)
{
	t_job	*new;

	if (!(new = init_job()))
		return (NULL);
	if (cmd)
		new->cmd = lst_to_str(cmd, 0);
	return (new);
}

static t_job	*create_job_argv(char **argv)
{
	t_job	*new;
	char	*cmd;

	if (!(cmd = ft_arrjoin(argv)))
		return (NULL);
	if (!(new = create_job(NULL)))
	{
		free(cmd);
		return (NULL);
	}
	new->cmd = cmd;
	return (new);
}

static t_proc	*add_proc_list(t_job *job, t_proc *new)
{
	new->job = job;
	if (job->foot_proc)
	{
		new->prev = job->foot_proc;
		job->foot_proc->next = new;
	}
	else
		job->head_proc = new;
	job->foot_proc = new;
	return (new);
}

t_proc			*create_proc(t_job **job, t_lexer_token *cmd)
{
	t_proc	*new;

	if (!*job && !(*job = create_job(cmd)))
		return (NULL);
	if (!(new = init_proc()))
		return (NULL);
	new->arg = arg_to_argv(cmd);
	new->cmd = cmd;
	new->envl = dup_envl(g_shell.envl);
	if (execute_assign_list(cmd, new) < 0)
		new->error = 125;
	else if (new->arg && !(new->is_builtin = check_builtin(new->arg[0])))
	{
		if ((new->find_error = find_command(new->path,
						new->arg[0], new->envl)) != 0)
			new->error = 127;
	}
	return (add_proc_list(*job, new));
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

int				create_background_job(t_lexer_token *amp)
{
	pid_t	pid;
	t_job	*job;
	t_proc	*proc;

	if ((pid = fork()) < 0)
		fatal_exit(SH_ENOMEM);
	if (pid > 0)
	{
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
		// TODO print jobspec
		// TODO set current_job if needed
		printer_char(&g_shell.err, '[');
		printer_ulong(&g_shell.err, job->jobspec);
		printer_bin(&g_shell.err, (uint8_t *)"] ", 2);
		printer_ulong(&g_shell.err, (size_t)pid);
		printer_endl(&g_shell.err);
		printer_flush(&g_shell.err);
		return (1);
	}
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
