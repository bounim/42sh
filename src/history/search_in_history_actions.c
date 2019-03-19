/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_history_actions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 17:16:59 by aguillot          #+#    #+#             */
/*   Updated: 2019/03/18 17:17:02 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	del_charac_in_search(void)
{
	printf("\nDEL\n");
	exit (1);
}

void	execute_search_command(void)
{
	printf("EXEC\n");
}

void	give_up_search(void)
{
	printf("\nGIVE UP\n");
}

void	back_to_readline(void)
{
	printf("\nBACK TO READLINE\n");
}

void	print_search_result(uint8_t *buff, size_t buff_len, t_history *curr)
{
	clean_screen();
	ft_putstr("(reverse-i-search)`");
	write(1, buff, buff_len);
	ft_putstr("\': ");
	write(1, curr->buf, curr->len);
}

void	find_in_history(uint8_t	*buff, size_t *len)
{
	t_history	*curr;

	curr = g_shell.hist.history;
	while (curr)
	{
		if (ft_strstr((char*)buff, (char*)curr->buf) != 0)
		{
			print_search_result(buff, *len, curr);
			break ;
		}
		curr = curr->bfr;
	}
}