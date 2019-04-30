/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_history.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <schakor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 14:41:06 by schakor           #+#    #+#             */
/*   Updated: 2019/04/24 15:17:29 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static t_history	*parse_histfile_content(uint8_t *cont)
{
	t_history	*ret;
	t_history	*new;
	uint8_t		**split_content;
	ssize_t		i;

	split_content = ft_u8_strsplit(cont, (uint8_t)'\n');
	ret = NULL;
	i = 0;
	while (split_content[i])
	{
		new = rl_new_hist(split_content[i]);
		ret = rl_add_hist(ret, new);
		g_shell.hist.history_size++;
		free(split_content[i]);
		i++;
	}
	free(split_content);
	return (ret);
}

static uint8_t		*get_histfile_content(void)
{
	uint8_t			*ret;
	uint8_t			buf[BUFF_SIZE + 1];
	int				fd;
	char			*histpath;
	ssize_t			rd;

	if (!(histpath = get_env_val(g_shell.envl, "HISTFILE")))
		return (NULL);
	if ((((fd = open(histpath, O_RDONLY)) < 0) || (read(fd, buf, 0) < 0))
			|| (!(ret = ft_u8_strnew(0))))
		return (NULL);
	while ((rd = read(fd, buf, BUFF_SIZE)))
	{
		check_nul_charac(buf, rd);
		buf[rd] = '\0';
		ret = ft_u8_strfjoin(ret, buf, 0);
	}
	if (close(fd) == -1)
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}

t_history			*init_shell_history(void)
{
	t_history	*ret;
	uint8_t		*cont;

	ft_memset(g_shell.hist.search_buff, 0, sizeof(*g_shell.hist.search_buff));
	g_shell.hist.search_len = 0;
	if (!(cont = get_histfile_content()))
		return (NULL);
	ret = parse_histfile_content(cont);
	free(cont);
	return (ret);
}
