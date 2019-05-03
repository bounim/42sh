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

static t_job	*create_job(t_lexer_token *cmd)
{
	t_job	*new;
	t_job	*cur;

	if (!(new = init_job()))
		return (NULL);
	if (cmd)
		new->cmd = lst_to_str(cmd, 0);
	if (!g_shell.head_job)
	{
		g_shell.head_job = new;
		return (new);
	}
	cur = g_shell.head_job;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
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

static t_proc	*add_proc_list(t_job **job, t_proc *new)
{
	if ((*job)->foot_proc)
	{
		new->prev = (*job)->foot_proc;
		(*job)->foot_proc->next = new;
	}
	else
		(*job)->head_proc = new;
	(*job)->foot_proc = new;
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
	new->job = *job;
	new->envl = dup_envl(g_shell.envl);
	if (execute_assign_list(cmd, new) < 0)
		new->error = 125;
	else if (new->arg && !(new->is_builtin = check_builtin(new->arg[0])))
	{
		if ((new->find_error = find_command(new->path,
						new->arg[0], new->envl)) != 0)
			new->error = 127;
	}
	return (add_proc_list(job, new));
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
	new->job = *job;
	new->envl = dup_envl(envl ? envl : g_shell.envl);
	ft_memmove(new->path, path, PATH_MAX + 1);
	return (add_proc_list(job, new));
}

int				create_background_job(t_lexer_token *amp)
{
	pid_t	pid;
	t_job	*job;

	if ((pid = fork()) < 0)
		fatal_exit(SH_ENOMEM);
	if (pid > 0)
	{
		if (!(job = create_job(NULL)))
			return (-1);
		job->pgid = pid;
		job->cmd = lst_to_str(amp, 1);
		job->background = 1;
		// TODO print new job: [jobspec] pgid
		return (1);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGWINCH, SIG_IGN);
	free_exec();
	g_shell.background = 1;
	g_shell.pgid = getpid();
	setpgid(0, g_shell.pgid);
	//clear_signals(); // FIXME may need to clear some signals (CHLD, STTIN, STTOU, STOP?)
	return (0);
}
