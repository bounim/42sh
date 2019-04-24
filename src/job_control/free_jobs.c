#include "twenty_one_sh.h"

void	free_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		ft_strdel(&arr[i]);
		i++;
	}
	free(arr);
}

void	free_proc(t_proc *proc)
{
	free_arr(proc->arg);
	//free env only if dup envl...
	free(proc);
}

void	free_job(t_job *job)
{
	t_proc	*proc;
	t_proc	*next;

	proc = job->head_proc;
	while (proc)
	{
		next = proc->next;
		free_proc(proc);
		ft_strdel(&job->cmd);
		proc = next;
	}
}

void	free_exec(void)
{
	t_job	*job;
	t_job	*next;

	job = g_shell.head_job;
	while (job)
	{
		next = job->next;
		free_job(job);
		job = next;
	}
}
