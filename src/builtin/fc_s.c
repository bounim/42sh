/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:31:18 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/25 15:31:20 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void	print_line_to_shell(uint8_t *buff)
{
	ft_putstr((char*)buff);
	ft_putchar('\n');
}

/*static void	send_line_to_lexer(uint8_t *line)
{
	t_lexer		lex;
	size_t		i;

	ft_memset(&lex, 0, sizeof(lex));
	i = 0;
	lexer(&lex, line + i, g_shell.line_size - i);
	//i += lex->i;
}*/

void		fc_s(int fc_range[2])
{
	int 		histsize;
	t_history	*curr;

	histsize = get_hist_full_size(g_shell.hist.history);
	curr = find_first_hist_line();
	if (fc_range[0] == histsize - 15 && fc_range[1] == histsize)
		fc_range[0] = fc_range[1];
	if (!(curr = find_specific_hist_line(fc_range[0], curr)))
		return ;
	rebuild_g_shell_line(curr->buf);
	print_line_to_shell(curr->buf);
	//send_line_to_lexer(curr->buf);
	//where to send the line?
}