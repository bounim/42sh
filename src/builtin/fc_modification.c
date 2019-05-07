/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_modification.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 17:55:13 by aguillot          #+#    #+#             */
/*   Updated: 2019/05/04 16:09:09 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	open_modif_file(int *fd, char path[PATH_MAX + 1], struct stat *sb)
{
	if ((*fd = open(path, O_RDONLY)) < 0)
	{
		write_error(path, "file can not be created");
		return (125);
	}
	if (stat(path, sb) != 0)
		write_error(path, "no such file or directory");
	else if (!(sb->st_mode & S_IRUSR))
		write_error(path, "permission denied");
	else if (!(S_ISREG(sb->st_mode)))
		write_error(path, "not a file");
	else
		return (0);
	return (1);
}

static int	build_buff(int fd, uint8_t **buff, struct stat *sb)
{
	int		rd;
	char	*r_stock;

	if (NULL == (r_stock = malloc(sb->st_size + 1)))
		return (1);
	r_stock[sb->st_size] = '\0';
	if ((rd = read(fd, r_stock, sb->st_size)) != sb->st_size)
	{
		write_error("fc", "write error: Bad file descriptor");
		return (1);
	}
	r_stock[rd] = '\0';
	(*buff) = (uint8_t *)r_stock;
	if (rd - 1 > 0 && (*buff)[rd - 1] != '\n')
		*(buff) = (uint8_t*)ft_strfjoin((char*)*buff, "\n", 0);
	else if (!(*buff)[0])
	{
		free(*buff);
		*buff = (uint8_t *)ft_strdup("\n");
	}
	return (0);
}

static int	manage_buff(int *fd, uint8_t **buff, char path[PATH_MAX + 1])
{
	int			ret;
	struct stat sb;

	if ((ret = open_modif_file(fd, path, &sb)) > 0)
		return (ret);
	if ((ret = build_buff(*fd, buff, &sb)) > 0)
		return (ret);
	return (0);
}

static int	fc_modification_end(uint8_t **buff, char ed_path[PATH_MAX + 1],
		char *editor, t_envl *envl)
{
	if (!buff || !*buff)
		return (1);
	if (find_command(ed_path, editor, envl) == -1)
	{
		write_error("command not found", editor);
		return (1);
	}
	return (0);
}

int			fc_modification(uint8_t **buff, t_envl *envl, char *editor, int len)
{
	char	path[PATH_MAX + 1];
	char	ed_path[PATH_MAX + 1];
	char	*buf[3];
	int		fd;
	int		ret;

	if (fc_modification_end(buff, ed_path, editor, envl))
		return (1);
	fd = 0;
	if ((ret = create_tmp_file(&fd, path, buff, len)) > 0)
		return (ret);
	ft_strdel((char **)buff);
	close(fd);
	buf[0] = editor;
	buf[1] = path;
	buf[2] = NULL;
	if (fast_exec(buf, ed_path, envl))
	{
		write_error("editor closed unexpectedly", editor);
		unlink(path);
		return (125);
	}
	ret = manage_buff(&fd, buff, path);
	unlink(path);
	return (ret);
}
