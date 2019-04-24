/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 13:45:08 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/22 16:48:58 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

//option -e est prio sur toutes les options, ensuite c'est s;

void		rebuild_charac_list(uint8_t *buff)
{
	int i;
	int len;

	i = 0;
	len = 0;
	rl_free_controler(FREE_ONLY_EDIT_CHAR_LIST);
	init_char_list();
	init_prompt(BASIC_PROMPT);
	while (buff[i])
	{
		len = ft_wchar_len(buff + i);
		add_char_to_list(buff + i, len, 0);
		i += len;
	}
}

static void	fc_s(int fc_range[2])
{
	int 		histsize;
	t_history	*curr;

	histsize = get_hist_full_size(g_shell.hist.history);
	curr = find_first_hist_line();
	if (fc_range[0] == histsize - 15 && fc_range[1] == histsize)
		fc_range[0] = fc_range[1];
	if (!(curr = find_specific_hist_line(fc_range[0], curr)))
		return ;
	//rebuild_charac_list(curr->buf);
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
		return (-1);
	build_fc_range(av, fc_range, index);
	printf("range: %d, range: %d\n", fc_range[0], fc_range[1]);
	if (check_fc_range(fc_range) == OUT_OF_RANGE)
		return (-1);
	fc_controler(fc_range, fc_opts, av, envl);
	return (1);
}
