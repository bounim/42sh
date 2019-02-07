/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 11:38:33 by khsadira          #+#    #+#             */
/*   Updated: 2019/02/06 16:23:53 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static char		**file_to_buffer(int fd, char **buffer)
{
	int		ret;
	char	buff[2];
	char	*str;

	buff[0] = 0;
	buff[1] = 0;
	str = NULL;
	while ((ret = read(fd, buff, 1)) > 0)
	{
		if (str == NULL)
			str = ft_strdup("");
		buff[ret] = '\0';
		str = ft_strfjoin(str, buff, 0);
	}
	if (str == NULL)
		return (NULL);
	close(fd);
	if (str)
		buffer = ft_strsplit(str, '\n');
	free(str);
	return (buffer);
}

static void		init_bufvar(t_bufvar *bufvar, char *str)
{
	bufvar->i_buf = ft_strlen(str);
	bufvar->len_buf = ft_strlen(str);
	bufvar->i_char = ft_wslen(str);
	bufvar->len_char = ft_wslen(str);
	bufvar->len_tot = ft_strlen(str);
}

void			rl_history_from_file(t_rl *rl, char *path)
{
	char		**buff;
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
	ft_arrdel(buff);
	free(path);
}

void			rl_file_from_history(t_rl *rl, char *path)
{
	int		fd;
	char	*str;

	path = ft_strfjoin(path, "/.21sh_history", 0);
	fd = open(path, O_WRONLY);
	if (fd < 0)
		fd = open(path, O_CREAT | O_WRONLY);
	if (fd > 0)
	{
		str = ft_strdup("");
		while (rl->history && rl->history->bfr)
			rl->history = rl->history->bfr;
		while (rl->history)
		{
			str = ft_strfjoin(str, rl->history->buf, 0);
			str = ft_strfjoin(str, "\n", 0);
			rl->history = rl->history->next;
		}
		if (str)
			write(fd, str, ft_strlen(str));
		free(str);
		free(path);
		close(fd);
	}
}
