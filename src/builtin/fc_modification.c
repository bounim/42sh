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

static int	create_tmp_file(int *fd, char path[PATH_MAX + 1], uint8_t **buff,
	int len)
{
	if ((*fd = random_file(path)) < 0)
	{
		ft_putstr_fd("open: file can not be created", 2);
		return (125);
	}
	write(*fd, *buff, len);
	if (lseek(*fd, 0, SEEK_SET) == -1)
		return (1);
	return (0);
}

static int	open_modif_file(int *fd, char path[PATH_MAX + 1], struct stat *sb)
{
	if ((*fd = open(path, O_RDONLY)) < 0)
	{
		write_error(path, "file can not be created");
		return (125);
	}
	if (stat(path, sb) != 0)
	{
		perror("");
		write_error(path, "no such file or directory");
		return (1);
	}
	if (!(sb->st_mode & S_IRUSR))
	{
		write_error(path, "permission denied");
		return (1);
	}
	else if (!(S_ISREG(sb->st_mode)))
	{
		write_error(path, "not a file");
		return (1);
	}
	return (0);
}

static int	build_buff(int fd, uint8_t **buff, struct stat *sb)
{
	int		rd;
	char	r_stock[sb->st_mode];

	if ((rd = read(fd, r_stock, sb->st_size)) != sb->st_size)
	{
		write_error("fc", "write error: Bad file descriptor");
		return (1);
	}
	r_stock[rd] = 0;
	(*buff) = (uint8_t *)ft_strdup(r_stock);
	if (*buff[rd - 1] != '\n')
		*(buff) = (uint8_t*)ft_strfjoin((char*)*buff, "\n", 0);
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

static void	fast_exec(char *buf[3], char ed_path[PATH_MAX + 1], t_envl *envl)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(ed_path, buf, envl_to_envarr(envl));
		exit(1);
	}
	wait(0);
}

int			fc_modification(uint8_t **buff, t_envl *envl, char *editor, int len)
{
	char	path[PATH_MAX + 1];
	char	ed_path[PATH_MAX + 1];
	char	*buf[3];
	int		fd;
	int		ret;

	fd = 0;
	if ((ret = create_tmp_file(&fd, path, buff, len)) > 0)
		return (ret);
	ft_strdel((char **)buff);
	close(fd);
	if (find_command(ed_path, editor, envl) == -1)
	{
		write_error("command not found", editor);
		return (1);
	}
	buf[0] = editor;
	buf[1] = path;
	buf[2] = NULL;
	fast_exec(buf, ed_path, envl);
	if ((ret = manage_buff(&fd, buff, path)) > 0)
		return (ret);
	return (0);
}
