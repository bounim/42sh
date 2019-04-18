/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 11:44:16 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/10 18:42:20 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

/*static t_job	*switch_ground(t_job *job, int foreground)
{
	format_job_info(job, "launched");
	if (!g_shell.is_interactive)
		wait_for_job(job);
	else if (foreground)
		put_in_foreground(job, 0);
	else
		put_in_background(job, 0);
	return (job);
}

static int		close_file_job(int std_file[2], int ret)
{
	if (std_file[0] != STDIN_FILENO)
		close(std_file[0]);
	if (std_file[1] != STDOUT_FILENO)
		close(std_file[1]);
	return (ret);
}*/

void			launch_job(t_job *job)
{
	t_proc	*cur;
	int		std_file[2];

	std_file[0] = STDIN_FILENO;
	cur = job->head_proc;
	if (!cur->next)
		launch_proc(cur);
	else
	{
		while (cur->next)
		{
			if (pipe(cur->tunnel) < 0)
				return ;//TODO set pipe error and exit clean --> close all previous pipes
			cur = cur->next;
		}
		cur = job->head_proc;
		while (cur)
		{
			launch_proc(cur);
			cur = cur->next;
		}
	}
	//int status;
	//waitpid(job->pgid, &status, WUNTRACED | WCONTINUED);
//	printf("exit code before wait %d\n", g_shell.exit_code);
//	g_shell.exit_code = get_return_status(status);
//	printf("exit code after wait %d\n", g_shell.exit_code);
	//job->foot_job->pid
}

/*void			launch_job(t_job *job, int foreground)
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
				return (ft_putstr_fd("pipe failed\n", 2));
			std_file[1] = my_pipe[1];
		}
		else
			std_file[1] = STDOUT_FILENO;
		if (proc->next || !proc->is_builtin)
			pid = fork();
		else
			pid = 42;
		if (pid < 0)
			return (ft_putstr_fd("fork failed\n", 2)); //TODO exit
		else if (pid == 0)
			launch_proc(proc, job->pgid, foreground, std_file);
		else
		{
			if (proc->is_builtin && !proc->next)
				start_builtin(proc->arg, g_shell.envl); //proc->env
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
		}
		std_file[0] = close_file_job(std_file, my_pipe[0]);
		proc = proc->next;
	}
	job = switch_ground(job, foreground);
}*/
