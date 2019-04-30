/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:05:24 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/05 15:14:16 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	check_nul_charac(uint8_t buf[BUFF_SIZE + 1], ssize_t rd)
{
	ssize_t			i;

	i = 0;
	while (i < rd)
	{
		if (buf[i] == '\0')
			fatal_exit(SH_ENOMEM);
		i++;
	}
}

void	build_search_buff(uint8_t *key, size_t *keylen)
{
	ft_memmove(g_shell.hist.search_buff
			+ g_shell.hist.search_len, key, *keylen);
	g_shell.hist.search_len += *keylen;
}

uint8_t	*list_to_buf(void)
{
	uint8_t		*ret;
	t_char		*tmp;
	int			buff_size;
	int			i;

	if ((tmp = skip_prompt(g_shell.edit.char_list.head)) == NULL)
		return (NULL);
	buff_size = get_buf_size(tmp, NULL);
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
