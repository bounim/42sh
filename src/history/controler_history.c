/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controler_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 13:33:25 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/22 16:19:09 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	switch_history(void)
{
	t_history	*head;
	int			i;
	uint8_t		*buf;

	i = 0;
	buf = list_to_buf();
	head = g_shell.hist.history;
	if (!buf || buf[0] == '\0')
		buf = (uint8_t*)ft_strdup("");
	while (i < g_shell.hist.history_save && g_shell.hist.history->bfr)
	{
		g_shell.hist.history = g_shell.hist.history->bfr;
		i++;
	}
	if (!ft_u8_strequ(g_shell.hist.history->buf, buf))
	{
		free(g_shell.hist.history->buf);
		if (!(g_shell.hist.history->buf = ft_u8_strdup(buf)))
			fatal_exit(SH_ENOMEM);
	}
	free(buf);
	g_shell.hist.history = head;
}

int		listlen(t_history *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->bfr;
	}
	return (i);
}

void	buff_to_charlist(uint8_t *buf)
{
	size_t		i;
	ssize_t		r;
	size_t		ulen;

	i = 0;
	ulen = ft_ustrlen(buf);
	while (i < ulen)
	{
		if ((r = ft_carac_size(buf + i, ulen - i)) == -1)
			return ;
		add_char_to_list(buf + i, r, FALSE);
		i += r;
	}
}

void	print_historyl(t_history *hist)
{
	int			i;
	int			len;

	i = 1;
	while (hist->bfr)
		hist = hist->bfr;
	while (hist)
	{
		len = 5 - ft_nblen(i);
		while (len--)
			ft_putchar(' ');
		ft_putnbr(i);
		ft_putstr("  ");
		ft_putstr((char *)hist->buf);
		if (hist->next)
			ft_putchar('\n');
		i++;
		hist = hist->next;
	}
	ft_putchar('\n');
}

void	print_history(void)
{
	if (g_shell.edit.cur_base_y < 0)
		g_shell.edit.cur_base_y = 0;
	rl_free_controler(FREE_ONLY_EDIT_CHAR_LIST);
	g_shell.edit.point_char = NULL;
	g_shell.edit.cur_base_x = 0;
	init_char_list();
	init_prompt(BASIC_PROMPT);
	buff_to_charlist(g_shell.hist.history->buf);
	if (g_shell.edit.cur_base_y < 0)
		g_shell.edit.cur_base_y = 0;
	clean_and_print();
}
