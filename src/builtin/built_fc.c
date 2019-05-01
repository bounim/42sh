/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 12:09:03 by aguillot          #+#    #+#             */
/*   Updated: 2019/05/01 12:09:05 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void		rebuild_g_shell_line(uint8_t *buff)
{
	int i;
	int len;

	i = 0;
	len = 0;
	if (g_shell.line)
		free(g_shell.line);
	if (!(g_shell.line = (uint8_t*)ft_strdup((char*)(buff))))
		fatal_exit(SH_ENOMEM);
	g_shell.line_size = ft_u8_strlen(buff);
	printf("%s\n", buff);
	sleep(1);
}

int			fc_controler(int fc_range[2], int fc_opts[5], char **av,\
		t_envl *envl)
{
	(void)av;
	(void)envl;
	if (fc_opts[L])
	{
		if (!fc_opts[R])
			print_fc_list(fc_opts, fc_range);
		else
			print_fc_list_reverse(fc_opts, fc_range);
		return (1);
	}
	if (fc_opts[S])
		fc_s(fc_range);
	return (1);
}

int		built_fc(char **av, t_envl *envl)
{
	int fc_opts[5];
	int index;
	int fc_range[2];

	(void)envl;
	if ((index = check_fc_opts(av, fc_opts)) == -1)
		return (2);
	build_fc_range(av, fc_range, index);
	if (check_fc_range(fc_range) == OUT_OF_RANGE)
		return (1);
	fc_controler(fc_range, fc_opts, av, envl);
	return (0);
}
