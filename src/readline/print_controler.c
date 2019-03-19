/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_controler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:17:40 by aguillot          #+#    #+#             */
/*   Updated: 2019/03/09 14:25:53 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	print_prompt(void)
{
	t_char	*curr;
	int		t;

	curr = g_shell.edit.char_list.head;
	t = 0;
	while (curr && curr->y_pos < 0)
	{
		curr = curr->next;
		t = 1;
	}
	while (curr && curr->is_prompt)
	{
		write(1, curr->charac, curr->len);
		curr = curr->next;
	}
}

void	clean_screen(void)
{
	size_t			i;
	struct winsize	max;
	int				x;
	int				y;

	ioctl(STDERR_FILENO, TIOCGWINSZ, &max);
	i = -1;
	x = g_shell.edit.cur_base_x;
	y = g_shell.edit.cur_base_y;
	if (y < 0)
	{
		while (y++ < 0)
			ft_putstr(tgetstr("sr", NULL));
		x = 0;
		y = 0;
	}
	ft_putstr(tgoto(tgetstr("cm", NULL), x, y));
	while (++i < max.ws_row)
		ft_putstr(tgetstr("dl", NULL));	
}

void	place_cursor_after_print(void)
{
	t_char	*prev;
	int		x;
	int		y;

	prev = g_shell.edit.point_char;
	/*if ((prev->x_pos + 1 == g_shell.edit.term_info.max.ws_col
				|| prev->charac[0] == '\n')
			&& prev->y_pos + 2 == g_shell.edit.term_info.max.ws_row)
	{
		ft_putstr("\n");
		return ;
	}*/
	x = get_x_pos(prev);
	y = get_y_pos(prev);
	ft_putstr(tgoto(tgetstr("cm", NULL), x, y));
}

int		find_print_from()
{
	int		ret;
	t_char	*curr;

	ret = 0;
	curr = find_first_non_prompt(g_shell.edit.char_list.head);
	if (!curr)
		return (-1);
	if (curr->y_pos >= 0)
		return (0);
	while (curr->x_pos != 0 && curr->y_pos != 0)
	{
		curr = curr->next;
		ret++;
	}
	return (ret);
}

void	clean_and_print(void)
{
	t_char		*curr;
	uint8_t		*buff;
	int			print_from;
	size_t		len;

	curr = g_shell.edit.char_list.head;
	clean_screen();
	print_prompt();
	if (!(buff = list_to_buf()))
	 	return ;
	if ((print_from = find_print_from()) == -1)
		return ;
	len = ft_ustrlen(buff + print_from);
	write(1, buff + print_from, len);
	/*while ((curr && curr->is_prompt == 1) || (curr && curr->y_pos < 0))
		curr = curr->next;
	while (curr)
	{
		write(1, curr->charac, curr->len);
		if (curr->charac[0] == '\n')
			ft_putstr(tgetstr("cr", NULL));
		curr = curr->next;
	}*/
	check_all_pos();
	place_cursor_after_print();
}