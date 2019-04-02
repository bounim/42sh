/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_controler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:17:40 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/02 18:48:02 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void		clean_screen_from(int x, int y)
{
	int				i;
	struct winsize	max;

	i = 0;
	ioctl(STDERR_FILENO, TIOCGWINSZ, &max);
	if (y < 0)
	{
		x = 0;
		y = 0;
	}
	ft_putstr(tgoto(tgetstr("cm", NULL), x, y));
	while (++i < max.ws_row)
		ft_putstr(tgetstr("dl", NULL));
}

void		place_cursor_after_print(t_char *curr, int max_x, int max_y)
{
	int		x;
	int		y;

	y = curr->y_pos;
	if ((x = curr->x_pos + 1) == max_x)
	{
		x = 0;
		if ((y += 1) == max_y)
			ft_putstr(tgetstr("sr", NULL));
	}
	ft_putstr(tgoto(tgetstr("cm", NULL), x, y));
}

static int	find_print_from(void)
{
	int		ret;
	t_char	*curr;

	ret = 0;
	curr = g_shell.edit.char_list.head;
	if (!curr)
		return (-1);
	if (curr->y_pos >= 0)
		return (0);
	while (curr->y_pos < 0)
	{
		curr = curr->next;
		ret += curr->len;
	}
	return (ret);
}

static void	align_with_y(int *lines_to_shift)
{
	while (*lines_to_shift > 0)
	{
		write(1, "\n", 1);
		(*lines_to_shift)--;
	}
}

void		clean_and_print(void)
{
	t_char		*curr;
	uint8_t		*buff;
	int			print_from;
	size_t		len;

	align_with_y(&g_shell.edit.lines_to_shift);
	clean_screen_from(g_shell.edit.cur_base_x, g_shell.edit.cur_base_y);
	if (!(curr = g_shell.edit.char_list.head))
		return ;
	if (!(buff = list_to_buff_print(curr, NULL)))
		return ;
	if ((print_from = find_print_from()) == -1)
		return ;
	len = ft_ustrlen(buff + print_from);
	write(1, buff + print_from, len);
	place_cursor_after_print(g_shell.edit.point_char,\
	g_shell.edit.term_info.max.ws_col, g_shell.edit.term_info.max.ws_row);
	free(buff);
}
