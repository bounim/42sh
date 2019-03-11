/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_history.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <schakor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 14:41:06 by schakor           #+#    #+#             */
/*   Updated: 2019/03/07 17:04:20 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"


static void			check_nul_charac(uint8_t buf[BUFF_SIZE + 1], ssize_t rd)
{
	ssize_t			i;

	i = 0;
	while (i < rd)
	{
		if (buf[i] == '\0')
		{
			fatal_exit(SH_ENOMEM);
			//To do : corrupt file '\0'; => in fatal_exit
		}
		i++;
	}
}

static uint8_t		*get_histfile_content()
{
	uint8_t			*ret;
	uint8_t			buf[BUFF_SIZE + 1];
	int				fd;
	char			*histpath;
	ssize_t			rd;

	if (!(histpath = ft_strjoin(get_env_val(g_shell.envl, "HOME"),
								"/.21sh_history")))
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

static void			build_tmp(uint8_t *tmp, uint8_t *cont, size_t i, size_t j)
{
	size_t			ind;

	ind = 0;
	while (j < i)
	{
		if (cont[j] == '\\')
			j++;
		tmp[ind++] = cont[j++];
	}
}

static size_t		skip_backslash(const uint8_t *str, size_t *i, size_t j, int bs)
{
	size_t			len;

	len = *i - j - bs;
	if (*i > 0 && str[*i - 1] != '\\')
		return (len);
	(*i)++;
	while (str[*i] && str[*i] != '\n')
		(*i)++;
	if (str[*i] == '\n' && str[*i - 1] == '\\')
		skip_backslash(str, i, j, bs++);
	return (len);
}

static t_history	*parse_histfile_content(uint8_t *cont)
{
	t_history	*ret;
	t_history	*new;
	uint8_t		*tmp;
	size_t 		i;
	size_t 		j;
	size_t		len;

	tmp = NULL;
	ret = NULL;
	i = 0;
	j = 0;
	while (cont[i])
	{
		if (cont[i] == '\n')
		{
			len = skip_backslash(cont, &i, j, 0);
			if (!(tmp = (uint8_t*)malloc(sizeof(uint8_t) * (len + 1)))) // on rajoute pas +1 parce que le i est a un \n quon veut pas
				fatal_exit(SH_ENOMEM);
			tmp[len] = '\0';
			build_tmp(tmp, cont, i, j);
			new = rl_new_hist(tmp);
			ret = rl_add_hist(ret, new);
			g_shell.hist.history_size++;
			i++;
			j = i;
		}
		i++;
	}
	return (ret);
}

t_history			*init_shell_history(void)
{
	t_history		*ret;
	uint8_t 		*cont;

	if (!(cont = get_histfile_content()))
		return (NULL);
	ret = parse_histfile_content(cont);
	return (ret);
}
