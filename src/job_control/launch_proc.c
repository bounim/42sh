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

int			get_return_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (1000 + WTERMSIG(status));
	else if (WIFSTOPPED(status))
		return (2000 + WSTOPSIG(status));
	return (1);
}

static void	wait_job(t_proc *proc)
{
	int		status;
	pid_t	wpid;
	t_proc	*cur;

	if (proc->next)
		return ;
	// TODO set job as launched?
	// TODO the rest is for foreground, background is other stuff
	tcsetpgrp(g_shell.term, proc->job->pgid);
	// TODO cont stuff (only for `fg`) goes here (DRY)
	// TODO ^^^^
	// FIXME wait job func
	status = 0;
	while (proc->job->running > 0 && (wpid = waitpid(WAIT_ANY /*-proc->job->head_proc->pid*/, &status, WUNTRACED/* | WCONTINUED*/)) >= 0) // TODO replace by WAIT_ANY when we do background
	{
		if (WIFSTOPPED(status))
		{
			kill(wpid, SIGTERM); // TODO
			kill(wpid, SIGCONT); // TODO
			continue ;
		}
		cur = proc->job->head_proc;
		while (cur)
		{
			if (wpid == cur->pid)
			{
				cur->completed = 1; // FIXME
				proc->job->running--;
				if (!cur->next)
				{
					if (WIFSIGNALED(status))
						g_shell.exit_code = 1000 + WTERMSIG(status);
					else
						g_shell.exit_code = WEXITSTATUS(status);
				}
				break ;
			}
			cur = cur->next;
		}
		status = 0;
	}
	// FIXME ^^^^
	tcsetpgrp(g_shell.term, g_shell.pgid);
	tcgetattr(g_shell.term, &proc->job->tmodes);
	cooked_terminal();
}

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
	tcsetpgrp(g_shell.term, proc->job->pgid); // FIXME don't do this in background
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

void		launch_proc(t_proc *proc)
{
	if (!proc->is_builtin || proc->next || proc->prev)
	{
		if ((proc->pid = fork()) < 0)
			return ; //TODO fork error
		else if (proc->pid > 0)
		{
			proc_parent(proc);
			return ;
		}
		proc_child(proc);
	}
	if (command_redir(proc->cmd) < 0)
		proc->error = 125;
	if (proc->error)
	{
		if (!proc->is_builtin || proc->next || proc->prev)
		{
			clean_shell();
			exit(proc->error);
		}
		g_shell.exit_code = proc->error;
		return ;
	}
	if (proc->is_builtin)
	{
		g_shell.exit_code = start_builtin(proc->arg, proc->envl);
		command_redir_restore(proc->cmd);
		if (proc->next || proc->prev)
		{
			clean_shell();
			exit(g_shell.exit_code);
		}
	}
	else
	{
		proc->env = envl_to_envarr(proc->envl);
		execve(proc->path, proc->arg, proc->env);
		command_redir_restore(proc->cmd);
		fatal_exit(7);
	}
}
