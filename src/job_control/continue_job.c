#include "twenty_one_sh.h"

void	mark_job_as_running(t_job *job)
{
	t_proc	*proc;

	proc = job->head_proc;
	while (proc)
	{
		proc->stop = 0;
		proc = proc->next;
	}
}

void	continue_job(t_job *job, int foreground)
{
	mark_job_as_running(job);
	if (foreground)
		put_in_foreground(job, 1);
	else
		put_in_background(job, 1);
}
