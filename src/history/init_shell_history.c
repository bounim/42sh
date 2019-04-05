/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_history.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <schakor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 14:41:06 by schakor           #+#    #+#             */
/*   Updated: 2019/04/05 15:14:44 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static uint8_t		*get_histfile_content(void)
{
	uint8_t			*ret;
	uint8_t			buf[BUFF_SIZE + 1];
	int				fd;
	char			*histpath;
	ssize_t			rd;

	if (!(histpath = ft_strdup(get_env_val(g_shell.envl, "HISTFILE"))))
		if (!(histpath = ft_strjoin(get_env_val(g_shell.envl, "HOME"),
								"/.42sh_history")))
			fatal_exit(SH_ENOMEM);
	if (((fd = open(histpath, O_RDONLY)) < 0) || read(fd, buf, 0) < 0)
		return (NULL);
	if (!(ret = ft_u8_strnew(0)))
		fatal_exit(SH_ENOMEM);
	while ((rd = read(fd, buf, BUFF_SIZE)))
	{
		check_nul_charac(buf, rd);
		buf[rd] = '\0';
		ret = ft_u8_strfjoin(ret, buf, 0);
	}
	if (close(fd) == -1)
		fatal_exit(SH_EINVAL);
	return (ret);
}

static uint8_t		*replace_by_space(uint8_t *buff)
{
	int	i;

	i = 0;
	while (buff[i])
	{
		if ((buff[i] < ' ' || buff[i] == 127) && buff[i] != '\n')
			buff[i] = ' ';
		i++;
	}
	return (buff);
}

static t_history	*parse_end(size_t i, size_t j, uint8_t *cont, uint8_t *tmp)
{
	t_history	*ret;
	t_history	*new;
	size_t		len;

	ret = NULL;
	while (cont[i])
	{
		if (cont[i] == '\n')
		{
			len = skip_backslash(cont, &i, j, 0);
			if (!(tmp = (uint8_t*)malloc(sizeof(uint8_t) * (len + 1))))
				fatal_exit(SH_ENOMEM);
			tmp[len] = '\0';
			build_tmp(tmp, cont, i, j);
			tmp = replace_by_space(tmp);
			new = rl_new_hist(tmp);
			ret = rl_add_hist(ret, new);
			g_shell.hist.history_size++;
			i++;
			j = i;
		}
		else
			i++;
	}
	return (ret);
}

static t_history	*parse_histfile_content(uint8_t *cont)
{
	uint8_t		*tmp;
	size_t		i;
	size_t		j;

	tmp = NULL;
	i = 0;
	j = 0;
	return (parse_end(i, j, cont, tmp));
}

t_history			*init_shell_history(void)
{
	t_history	*ret;
	uint8_t		*cont;

	ft_memset(g_shell.hist.search_buff, 0, sizeof(*g_shell.hist.search_buff));
	g_shell.hist.search_len = 0;
	g_shell.hist.search_point = NULL;
	g_shell.hist.buf = NULL;
	if (!(cont = get_histfile_content()))
		return (NULL);
	ret = parse_histfile_content(cont);
	return (ret);
}
