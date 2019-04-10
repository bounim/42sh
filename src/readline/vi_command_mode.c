/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_command_mode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:20:17 by schakor           #+#    #+#             */
/*   Updated: 2019/04/05 19:53:58 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void		vi_command_mode(void)
{
	move_left();
	g_shell.edit.edit_mode = MODE_VI_COMMAND;
}

void			invoke_vi(void)
{
	int			pid;
	char		**env;
	char 		*argv[5];

	//vim -c ':exe "normal iTEXT"' filename.txt
	argv[0] = ft_strdup("/usr/bin/vim");
	argv[1] = ft_strdup("-c");
	argv[2] = ft_strjoin("':exe \"normal i", (char *)list_to_buf());
	argv[2] = ft_strjoin(argv[2], "\"'");
	exit(1);
	argv[3] = ft_strdup("/tmp/vi-file-edit.txt");
	argv[4] = NULL;
	if ((pid = fork()) == 0)
	{
		env = envl_to_envarr(g_shell.envl);
		execve("/usr/bin/vim", argv, env);
		ft_arrdel(env);
		ft_arrdel(argv);
	}
	else if (pid < 0)
		fatal_exit(SH_EINVAL);
	wait(&pid);
}

void			treat_as_comment(void)
{
	t_char		*tmp;
	t_char		*new;

	tmp = g_shell.edit.char_list.head;
	while (tmp->next && tmp->is_prompt == TRUE)
		tmp = tmp->next;
	if (!(new = (t_char *)malloc(sizeof(*new))))
		fatal_exit(SH_ENOMEM);
	ft_memset(new->charac, '\0', sizeof(new->charac));
	new->charac[0] = '#';
	new->len = 1;
	if (tmp->is_prompt == TRUE)
	{
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	else
	{
		new->prev = tmp->prev;
		new->prev->next = new;
		new->next = tmp;
		tmp->prev = new;
	}
	update_all_pos();
	clean_and_print();
	return_fn();
}
