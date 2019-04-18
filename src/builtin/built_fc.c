/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 13:45:08 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/16 13:45:10 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

//option -e est prio sur toutes les options, ensuite c'est s;

int 	get_nb_of_zeros(int nb)
{
	int ret;

	ret = 0;
	while (nb /= 10)
		ret++;
	return (ret);
}


//Il y a inversement avec l'ordre de la liste. ca peut venir de head qui n'est pas head mais qui est tail.
//faire -r ensuite.
// faire le sans argument ensuite.
//listing sera done
void	print_fc_list(int fc_opts[5], int range_nb, int fc_range[2])
{
	t_history 	*head;
	int 		nb_o_zer;

	head = find_first_hist_line();
	if (!(head = find_specific_hist_line(fc_range[0], head)))
		return ;
	if (range_nb == NUMBER)
		fc_range[1] = get_hist_full_size(g_shell.hist.history);
	while (head && fc_range[0] <= fc_range[1])
	{
		if (fc_opts[N])
			write(1, "         ", 7);
		else
		{
			ft_putstr(ft_itoa(fc_range[0]));
			nb_o_zer = 6 - get_nb_of_zeros(fc_range[0]);		
			while (nb_o_zer--)
				write(1, " ", 1);
		}
		write(1, head->buf, ft_u8_strlen(head->buf));
		write(1, "\n", 1);
		fc_range[0]++;
		head = head->next;
	}
}

int 	fc_controler(int range_nb, int fc_range[2], int fc_opts[5], char **av, t_envl *envl)
{
	(void)av;
	(void)envl;
	if (fc_opts[L])
	{
		print_fc_list(fc_opts, range_nb, fc_range);
		return (1);
	}
	return (1);
}

int		built_fc(char **av, t_envl *envl)
{
	int fc_opts[5];
	int index;
	int fc_range[2];
	int range_nb;

	(void)envl;
	if ((index = check_fc_opts(av, fc_opts)) == -1)
		return (-1);
	//printf("E: %d, L: %d, N: %d, R: %d, S: %d\n", fc_opts[0], fc_opts[1], fc_opts[2], fc_opts[3], fc_opts[4]);
	range_nb = build_fc_range(av, fc_range, index);
	if ((range_nb = check_fc_range(fc_range, range_nb)) == OUT_OF_RANGE)
		return (-1);
	fc_controler(range_nb, fc_range, fc_opts, av, envl);
	return (1);
}