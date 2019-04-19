/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 13:45:08 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/19 15:56:17 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

//option -e est prio sur toutes les options, ensuite c'est s;

void	print_usage_fc(char opt)
{
	if (opt != 'e' && opt != 'l' && opt != 'n' && opt != 'r' && opt != 's')
	{
		ft_putstr("21sh: fc: -");
		ft_putchar(opt);
		ft_putstr(": invalid option\n");
		ft_putstr("fc: usage: fc [-e ename] [-nlr]\
			[first] [last] or fc -s [pat=rep] [cmd]");
	}
	else
		ft_putstr("21sh: fc: history specification out of range");
}

void	print_fc_list_reverse(int fc_opts[5], int fc_range[2])
{
	t_history	*curr;
	int			blank_nb;
	char		*line;

	curr = find_first_hist_line();
	if (!(curr = find_specific_hist_line(fc_range[1], curr)))
		return ;
	while (curr && fc_range[1] >= fc_range[0])
	{
		if (fc_opts[N])
			write(1, "         ", 7);
		else
		{
			line = ft_itoa(fc_range[1]);
			ft_putstr(line);
			free(line);
			blank_nb = 6 - ft_get_nb_len(fc_range[0]);
			while (blank_nb--)
				write(1, " ", 1);
		}
		ft_putstr((char*)curr->buf);
		write(1, "\n", 1);
		curr = curr->bfr;
		fc_range[1]--;
	}
}

void	print_fc_list(int fc_opts[5], int fc_range[2])
{
	t_history	*curr;
	int			blank_nb;
	char		*line;

	curr = find_first_hist_line();
	if (!(curr = find_specific_hist_line(fc_range[0], curr)))
		return ;
	while (curr && (fc_range[0] <= fc_range[1]))
	{
		if (fc_opts[N])
			write(1, "         ", 7);
		else
		{
			line = ft_itoa(fc_range[0]);
			ft_putstr(line);
			free(line);
			blank_nb = 6 - ft_get_nb_len(fc_range[0]);
			while (blank_nb--)
				write(1, " ", 1);
		}
		ft_putstr((char*)curr->buf);
		write(1, "\n", 1);
		curr = curr->next;
		fc_range[0]++;
	}
}

int		fc_controler(int fc_range[2], int fc_opts[5], char **av, t_envl *envl)
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
	if (check_fc_range(fc_range) == OUT_OF_RANGE)
		return (-1);
	fc_controler(fc_range, fc_opts, av, envl);
	return (1);
}
