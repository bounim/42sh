/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 11:24:42 by schakor           #+#    #+#             */
/*   Updated: 2019/02/06 16:36:58 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void				init_env_var(t_shell *sh, char **env)
{
	sh->env = ft_arrdup(env);
	sh->envl = envarr_2_envl(env);
	sh->sigtstp_sig = 0;
}

t_shell					*init_shell(int ac, char **av, char **env)
{
	t_shell				*sh;

	(void)ac;
	(void)av;
	sh = singleton_shell();
	init_env_var(sh, env);
	init_terminal(sh);
	printer_init(&sh->out, STDOUT_FILENO);
	printer_init(&sh->err, STDERR_FILENO);
	return (sh);
}

t_shell					*singleton_shell(void) // TODO remove
{
	static t_shell		*ret = NULL;

	if (!ret)
		if (!(ret = (t_shell *)malloc(sizeof(*ret))))
			fatal_exit(ret, SH_ENOMEM);
	return (ret);
}

void					run_shell(t_shell *sh) // XXX
{
	t_bool				run;

	run = TRUE;
	while (run == TRUE)
	{
		readline(sh);
		write(1, "\n", 1);
		ft_putstr(tgetstr("cr", NULL));
		ft_putstr(sh->line);
		if (ft_strcmp(sh->line, "history") == 0)
			;
		else if (ft_strcmp(sh->line, "exit") == 0)
		{
			reset_terminal(sh);
			exit(EXIT_FAILURE); // FIXME why failure
		}
		write(1, "\n", 1);
		ft_putstr(tgetstr("cr", NULL));
	}
}
