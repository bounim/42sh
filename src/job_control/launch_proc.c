/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_proc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 18:58:21 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/24 15:29:27 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void	proc_parent(t_proc *proc)
{
	proc->job->running++;
	if (proc->job->pgid == 0)
		proc->job->pgid = proc->pid;
	if (proc->prev)
		close(proc->prev->tunnel[0]);
	if (proc->next)
		close(proc->tunnel[1]);
	wait_job(proc);
}

static void	proc_child(t_proc *proc)
{
	t_proc *cur;

	if (proc->job->pgid == 0)
		proc->job->pgid = getpid();
	setpgid(0, proc->job->pgid);
	tcsetpgrp(g_shell.term, proc->job->pgid);
	clear_signals();
	if (proc->prev)
		dup2(proc->prev->tunnel[0], STDIN_FILENO);
	if (proc->next)
		dup2(proc->tunnel[1], STDOUT_FILENO);
	cur = proc->job->head_proc;
	while (cur->next)
	{
		close(cur->tunnel[0]);
		close(cur->tunnel[1]);
		cur = cur->next;
	}
}

static int	launch_proc_error(t_proc *proc)
{
	if (proc->error)
	{
		if (proc->find_error)
			exec_error(proc->arg[0], proc->find_error);
		g_shell.exit_code = proc->error;
		if (!proc->is_builtin || proc->next || proc->prev)
		{
			if (proc->error != 125)
				command_redir_restore(proc->cmd);
			clean_shell();
			exit(g_shell.exit_code);
		}
		return (-1);
	}
	return (0);
}

static void	launch_proc_end(t_proc *proc)
{
	if (!proc->arg || proc->is_builtin)
	{
		g_shell.exit_code = proc->arg ? start_builtin(proc->arg,
				proc->envl) : 0;
		command_redir_restore(proc->cmd);
		if (proc->next || proc->prev)
		{
			clean_shell();
			exit(g_shell.exit_code);
		}
	}
	else
	{
		if (!(proc->env = envl_to_envarr(proc->envl)))
			fatal_exit(SH_ENOMEM);
		close_fd_before_exec(proc->cmd);
		execve(proc->path, proc->arg, proc->env);
		fatal_exit(7);
	}
}

void		launch_proc(t_proc *proc)
{
	if ((proc->arg && !proc->is_builtin) || proc->next || proc->prev)
	{
		if ((proc->pid = fork()) < 0)
			fatal_exit(SH_ENOMEM);
		else if (proc->pid > 0)
		{
			proc_parent(proc);
			return ;
		}
		proc_child(proc);
	}
	if (command_redir(proc->cmd) < 0)
		proc->error = 125;
	if (launch_proc_error(proc) < 0)
		return ;
	launch_proc_end(proc);
}
