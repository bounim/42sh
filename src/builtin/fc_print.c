/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 16:39:33 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/22 16:38:30 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	print_usage_fc(char opt)
{
	if (opt != 'e' && opt != 'l' && opt != 'n' && opt != 'r' && opt != 's')
	{
		ft_putstr("21sh: fc: -");
		ft_putchar(opt);
		ft_putstr(": invalid option\n");
		ft_putstr("fc: usage: fc [-e ename] [-nlr]\
			[first] [last] or fc -s [pat=rep] [cmd]\n");
	}
	else
		ft_putstr("21sh: fc: history specification out of range\n");
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
