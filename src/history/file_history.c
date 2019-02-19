/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 11:38:33 by khsadira          #+#    #+#             */
/*   Updated: 2019/02/18 17:11:02 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static uint8_t		**file_to_buffer(int fd, uint8_t **buffer)
{
	int			ret;
	uint8_t		buff[2];
	uint8_t		*str;

	buff[0] = 0;
	buff[1] = 0;
	str = NULL;
	while ((ret = read(fd, buff, 1)) > 0)
	{
		if (str == NULL)
			str = ft_u8_strnew(0);
		buff[ret] = '\0';
		str = ft_u8_strfjoin(str, buff, 0);
	}
	if (str == NULL)
		return (NULL);
	close(fd);
	if (str)
		buffer = ft_u8_strsplit(str, '\n');
	free(str);
	return (buffer);
}

static void		init_bufvar(t_bufvar *bufvar, uint8_t *str)
{
	bufvar->i_buf = ft_u8_strlen(str);
	bufvar->len_buf = ft_u8_strlen(str);
	bufvar->i_char = ft_wslen((char *)str);
	bufvar->len_char = ft_wslen((char *)str);
	bufvar->len_tot = ft_u8_strlen(str);
}

void			rl_history_from_file(t_rl *rl, char *path)
{
	uint8_t		**buff;
	int			i;
	int			fd;
	t_history	*new_ele;
	t_bufvar	bufvar;

	path = ft_strfjoin(path, "/.21sh_history", 0);
	buff = NULL;
	i = 0;
	fd = open(path, O_RDWR | O_CREAT, 0666);
	if (fd < 0)
		return ;
	buff = file_to_buffer(fd, buff);
	close(fd);
	while (buff && buff[i])
	{
		rl->history_size++;
		init_bufvar(&bufvar, buff[i]);
		new_ele = rl_new_hist(buff[i], bufvar);
		rl->history = rl_add_hist(rl->history, new_ele);
		i++;
	}
	ft_arrdel((char**)buff);
	free(path);
}

void			rl_file_from_history(t_rl *rl, char *path)
{
	int			fd;
	uint8_t		*str;
	t_history	*tmp;

	path = ft_strfjoin(path, "/.21sh_history", 0);
	fd = open(path, O_WRONLY);
	if (fd < 0)
		fd = open(path, O_CREAT | O_WRONLY);
	if (fd > 0)
	{
		tmp = rl->history;
		str = ft_u8_strnew(0);
		while (tmp && tmp->bfr)
			tmp = tmp->bfr;
		while (tmp)
		{
			str = ft_u8_strfjoin(str, tmp->buf, 0);
			str = ft_u8_strfjoin(str, (uint8_t *)"\n", 0);
			tmp = tmp->next;
		}
		if (str)
			write(fd, str, ft_u8_strlen(str));
		free(str);
		free(path);
		close(fd);
	}
}
