/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_proc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 18:58:21 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/09 10:14:34 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	set_signal_dfl(void)
{
	//signal(SIGINT, SIG_DFL);
	//signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
} //a rajouter

/*static void	dup_close_file(int std_file[2])
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
}*/

/*int			wait_process(t_proc *proc)
{
	int		status;
	pid_t	wpid;

	while (1)
	{
		status = 0;
		wpid = waitpid(proc->pid, &status, 0WUNTRACED);
		//printf("<waitpid:exited=%d,signaled=%d,stopped=%d>\n", WIFEXITED(status), WIFSIGNALED(status), WIFSTOPPED(status));
		if (WIFEXITED(status))
		{
			int c = WEXITSTATUS(status);
			printf("Exit code = %d\n", c);
			g_shell.exit_code = c;
			break ;
		}
		else if (WIFSIGNALED(status))
		{
			//el
		}
	}
	return (0);
}*/
int			get_return_status(int status)
{
	if (WIFEXITED(status))
		printf("child exited, status = %d\n", WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		puts("signal");
	else if (WIFSTOPPED(status))
		puts("Stopped");
	//return (0);
	return (WEXITSTATUS(status));
}

void		launch_proc(t_proc *proc)
{
	pid_t	pid;
	int		status;

	if (proc->next || !proc->is_builtin)
	{
		set_signal_dfl();
		pid = fork();
		if (pid < 0)
			return ; //TODO fork error
		else if (pid > 0)
		{
			if (proc->prev)
				close(proc->prev->tunnel[0]);
			if (proc->next)
				close(proc->tunnel[1]);
			//proc->job->pgid = pid; //A REMETTRE
			if (!proc->next)
			{
				waitpid(pid, &status, WUNTRACED | WCONTINUED);
				g_shell.exit_code = get_return_status(status);
			}
			return ;
		}
		/*if (g_shell.is_interactive)
		{
			pid = getpid();
		}*/
		//setpgid(0, g_shell.pgid);
		//tcsetpgrp(g_shell.term, g_shell.pgid or getpid()); // TODO in fg
		if (proc->prev)
		{
			dup2(proc->prev->tunnel[0], STDIN_FILENO);
			close(proc->prev->tunnel[0]);
		}
		if (proc->next)
		{
			dup2(proc->tunnel[1], STDOUT_FILENO);
			close(proc->tunnel[1]);
		}
		if (command_redir(proc->cmd) < 0 || execute_assign_list(proc->cmd, proc) < 0)
		{
			fatal_exit(g_shell.exit_code); // TODO leaks
		}
		if (proc->is_builtin)
		{
			start_builtin(proc->arg, proc->envl);
			exit(0); // TODO leaks
		}
		else
		{
			proc->env = envl_to_envarr(proc->envl);
			execve(proc->path, proc->arg, proc->env);
			command_redir_restore(proc->cmd);
			fatal_exit(7); // TODO leaks
		}
	}
	else
	{
		if (command_redir(proc->cmd) < 0)
		{
			g_shell.exit_code = 125;
			return ;
		}
		if (execute_assign_list(proc->cmd, proc) < 0)
			g_shell.exit_code = 125;
		else
			start_builtin(proc->arg, proc->envl);
		command_redir_restore(proc->cmd);
	}
}

/*void		launch_proc(t_proc *proc, pid_t pgid,
						int foreground, int std_file[2])
{
	pid_t	pid;

	if (g_shell.is_interactive)
	{
		pid = getpid();
		if (pgid == 0)
			pgid = pid;
		setpgid(pid, pgid);
		if (foreground)
			tcsetpgrp(g_shell.term, pgid);
		set_signal_dfl();
	}
	dup_close_file(std_file);
	ft_putendl("launch proc");
	if (command_redir(proc->cmd) < 0 || execute_assign_list(proc->cmd, proc) < 0)
	{
		g_shell.exit_code = 125;
		if (proc->is_fork)
			fatal_exit(g_shell.exit_code); // TODO leaks
		return ;
	}
	if (!proc->is_builtin)
	{
		proc->env = envl_to_envarr(proc->envl);
		execve(proc->path, proc->arg, proc->env);
		command_redir_restore(proc->cmd);
		fatal_exit(7);
	}
	start_builtin(proc->arg, proc->envl);
	command_redir_restore(proc->cmd);
	if (proc->is_fork)
		exit(1);
}*/
