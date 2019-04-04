/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_proc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 18:58:21 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/04 19:00:40 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void	set_signal_dfl(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}

static void	dup_close_file(int std_file[2])
{
	if (std_file[0] != STDIN_FILENO)
	{
		dup2(std_file[0], STDIN_FILENO);
		close(std_file[0]);
	}
	if (std_file[1] != STDOUT_FILENO)
	{
		dup2(std_file[1], STDOUT_FILENO);
		close(std_file[1]);
	}
}

void	launch_proc(t_proc *proc, pid_t pgid, int foreground, int std_file[2])
{
	pid_t	pid;

	if (g_shell.is_interactive)
	{
		pid = getpid();
		if (pgid == 0)
			pgid = pid;
		setpgid(pid, pgid);
		if (foreground)
			my_tcsetpgrp(g_shell.term, pgid);
		set_signal_dfl();
	}
	dup_close_file(std_file);
	if (!proc->is_builtin)
	{
		execve(proc->path, proc->arg, proc->env);
		fatal_exit(7);
	}
	start_builtin(proc->arg, g_shell.envl);
}
