/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 11:44:16 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/04 18:59:50 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	launch_job(t_job *job, int foreground)
{
	t_proc	*proc;
	pid_t	pid;
	int		my_pipe[2];
	int		std_file[2];

	std_file[0] = STDIN_FILENO;
	proc = job->head_proc;
	while (proc)
	{
		if (proc->next)
		{
			if (pipe(my_pipe) < 0)	
			{
				ft_putstr_fd("pipe failed\n", 2);
				return ;
			}
			std_file[1] = my_pipe[1];
		}
		else
			std_file[1] = STDOUT_FILENO;
		if (proc->next || !proc->is_builtin)
		{
			printf("fork created\n");
			pid = fork();
		}
		if (pid == 0)
			launch_proc(proc, job->pgid, foreground, std_file);
		else if (proc->is_builtin && !proc->next)
			start_builtin(proc->arg, g_shell.envl);
		else if (pid < 0)
		{
			ft_putstr_fd("fork failed\n", 2);
			return ;
		}
		else
		{
			proc->pid = pid;
			if (g_shell.is_interactive)
			{
				if (!job->pgid)
					job->pgid = pid;
				setpgid(pid, job->pgid);
			}
		}
		if (std_file[0] != STDIN_FILENO)
			close(std_file[0]);
		if (std_file[1] != STDOUT_FILENO)
			close(std_file[1]);
		std_file[0] = my_pipe[0];
		proc = proc->next;
	}
	format_job_info(job, "launched");
	if (!g_shell.is_interactive)
		wait_for_job(job);
	else if (foreground)
		put_in_foreground(job, 0);
	else
		put_in_background(job, 0);
}
