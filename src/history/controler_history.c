/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controler_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 13:33:25 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/26 12:53:55 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static t_char	*skip_prompt(t_char *head)
{
	while (head && head->is_prompt == 1)
		head = head->next;
	return (head);
}

static int		get_buf_size(t_char *head)
{
	int	buff_size;

	buff_size = 0;
	while (head)
	{
		buff_size += head->len;
		head = head->next;
	}
	return (buff_size);
}

uint8_t			*list_to_buf(void)
{
	uint8_t		*ret;
	t_char		*tmp;
	int			buff_size;
	int			i;

	if ((tmp = skip_prompt(g_shell.edit.char_list.head)) == NULL)
		return (NULL);
	buff_size = get_buf_size(tmp);
	if (!(ret = (uint8_t*)malloc(sizeof(uint8_t) * (buff_size + 1))))
	{
		fatal_exit(SH_ENOMEM);
		return (NULL);
	}
	ret[buff_size] = '\0';
	i = 0;
	while (tmp)
	{
		ft_memmove(ret + i, tmp->charac, tmp->len);
		i += tmp->len;
		tmp = tmp->next;
	}
	return (ret);
}

void	switch_history(void)
{
	t_history	*head;
	int			i;
	uint8_t 	*buf;

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
		free(buf);
	}
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

void		buff_to_charlist(uint8_t *buf)
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
		clean_and_print();
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
		ft_putu8str(hist->buf);
		if (hist->next)
			ft_putchar('\n');
		i++;
		hist = hist->next;
	}
	ft_putchar('\n');
}

void	print_history(void)
{
	uint8_t *prompt;

	//free_all()
	g_shell.edit.point_char = NULL;
	g_shell.edit.cur_base_x = 0;
	init_char_list();
	init_prompt(BASIC_PROMPT);
	prompt = prompt_to_buff(&g_shell.edit.char_list);
	print_prompt(prompt, ft_ustrlen(prompt));
	free(prompt);
	buff_to_charlist(g_shell.hist.history->buf);
	clean_and_print(); //YEN A 2 UN DANS BUFF TO CHARLIST LAUTRE LA
}
