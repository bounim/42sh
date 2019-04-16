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

//parser, check la syntaxe de la phrase, 
//if cest du -, on check les options, on les sets, ensuite on teste le range, qu'on peut mettre dans un tableau;

t_history	*find_specific_hist_line(int line, t_history *head)
{
	int i;

	i = 0;
	while (i != line && head)
	{
		i++;
		head = head->next;
	}
	if (i == line)
		return (head);
	return (NULL);
}

int 	check_one_nb(int fc_value, t_history *head)
{
	if (find_specific_hist_line(fc_value, head) != NULL)
		return (1);
	print_usage_fc('e');
	return (-1);
}

int		check_a_range(int fc_range[2], t_history *head)
{
	(void)fc_range;
	(void)head;
	return (0);
}

int		check_fc_range(int fc_range[2], int range_nb)
{
	t_history 	*head;
	//int			line_nb;

	head = find_first_hist_line();
	if (range_nb == 0)
		return (0);
	if (range_nb == 1)
	{
		if(check_one_nb(fc_range[0], head) == 1)
			return (1);
		return (-1);
	}
	if (range_nb == 2)
	{
		if (check_a_range(fc_range, head) == 1)
			return (2);
		return (-1);
	}
	return (1);
}

int		build_fc_range(char **av, int fc_range[2], int i)
{
	int first;
	int last;

	if (!av[i])
		return (0);//ca veut dire pas de range.
	first = ft_atoi(av[i]);
	i++;
	if (!av[i])
		return (1);//une seule valeur
	last = ft_atoi(av[i]);
	fc_range[0] = first;
	fc_range[1] = last;
	printf("first %d, last %d\n", first, last);
	return (2);//2 valeurs
}

int		built_fc(char **av, t_envl *envl)
{
	int fc_opts[4];
	int index;
	int fc_range[2];
	int range_nb;

	(void)envl;
	if ((index = check_fc_opts(av, fc_opts)) == -1)
		return (-1);
	if ((nb_range = build_fc_range(av, fc_range, index)) == -1)
		return (-1);
	if (range_nb > 0)
		if (check_fc_range(fc_range, range_nb))
			return (-1);
	return (1);
}