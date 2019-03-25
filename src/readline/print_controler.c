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

void	print_prompt(uint8_t *prompt, size_t prompt_len)
{
	write(1, prompt, prompt_len);
}

void	clean_screen_from(int x, int y)
{
	int 			i;
	struct winsize	max;

	i = 0;
	ioctl(STDERR_FILENO, TIOCGWINSZ, &max);
	ft_putstr(tgoto(tgetstr("cm", NULL), x, y));
	while (++i < max.ws_row)
		ft_putstr(tgetstr("dl", NULL));
}

/*void	clean_screen(void)
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
}*/

void	place_cursor_after_print(void)
{
	t_char	*curr;
	int 	max_x;
	int		x;
	int		y;

	curr = g_shell.edit.point_char;
	max_x = g_shell.edit.term_info.max.ws_col;
	/*if ((prev->x_pos + 1 == g_shell.edit.term_info.max.ws_col
				|| prev->charac[0] == '\n')
			&& prev->y_pos + 2 == g_shell.edit.term_info.max.ws_row)
	{
		ft_putstr("\n");
		return ;
	}*/
	//x = get_x_pos(curr, g_shell.edit.term_info.max.ws_col);
	//y = get_y_pos(curr, g_shell.edit.term_info.max.ws_col,\g_shell.edit.term_info.max.ws_row);
	y = g_shell.edit.point_char->y_pos;
	if ((x = g_shell.edit.point_char->x_pos + 1) == max_x)
	{
		x = 0;
		if ((y += 1) == max_x)
			ft_putstr(tgetstr("sr", NULL));	
	}
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

void	align_with_y(int base_y, int *prev_base_y)
{
	if (*prev_base_y > base_y)
	{
		write(1, "\n", 1);
		*prev_base_y = base_y;
	}
}

void	clean_and_print(void)
{
	t_char		*curr;
	uint8_t		*buff;
	int			print_from;
	size_t		len;

	align_with_y(g_shell.edit.cur_base_y, &g_shell.edit.prev_base_y); //ceci devrait remplacer le scroll du precedant clean_screen();
	clean_screen_from(g_shell.edit.cur_base_x, g_shell.edit.cur_base_y);
	curr = g_shell.edit.char_list.head;
	buff = prompt_to_buff(&g_shell.edit.char_list);
	print_prompt(buff, ft_ustrlen(buff));
	free(buff);
	if (!(buff = list_to_buf()))
	 	return ;
	if ((print_from = find_print_from()) == -1)
		return ;
	len = ft_ustrlen(buff + print_from);
	write(1, buff + print_from, len);
	//check_all_pos();
	place_cursor_after_print();
}