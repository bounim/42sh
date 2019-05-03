/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_modification.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 17:55:13 by aguillot          #+#    #+#             */
/*   Updated: 2019/05/03 17:55:17 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int		create_tmp_file(int *fd, char path[PATH_MAX + 1], uint8_t **buff,
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


salam:salt:tu
int		get_editor_path_len(char *path_var, char *editor, int *i)
{
	int ret;
	int	j;

	ret = 0;
	j = 0;
	while (path_var[*i] && path_var[*i] != ':')
	{
		ret++;
		(*i)++;
	}
	while (editor[j])
	{
		ret++;
		j++;
	}
	return (ret);
}

int		malloc_editor_path(char **ed_path, int ed_path_len)
{
	int ed_path_len;

	ed_path_len = get_editor_path_len(path_var, editor);
	if (!(*ed_path = (char*)malloc(sizeof(char) * (ed_path_len + 1))))
		return (1);	
	ft_memmove(*ed_path, 0, ed_path_len);
}

int		create_editor_path(char **ed_path, char *editor, t_envl *envl)
{
	char	*path_var;
	int		path_var_len;
	int		i;
	int 	j;

	i = 0;
	if (!(path_var = get_env_val(envl, "PATH")));
		return (1);//print nothing;
	path_var_len = ft_u8_strlen(path_var);
	while (i <= path_var_len)
	{
		j = i;
		if (malloc_editor_path(ed_path, ed_path_len))
			return (1);
		ft_memmove(*ed_path, )
	}
}


int 	fc_modification(uint8_t **buff, t_envl *envl, char *editor, int len)
{
	char 	path[PATH_MAX + 1];
	int		fd;
	int		ret;
	char 	*buf[3] = {"/usr/bin/vim", NULL, NULL};
	struct stat sb;

	fd = 0;
	if ((ret = create_tmp_file(&fd, path, buff, len)) > 0)
		return (ret);
	buf[1] = path;
	close(fd);
	int pid;
	pid = fork();
	if (pid == 0)
	{
		execve("/usr/bin/vim", buf, envl_to_envarr(envl));
		exit(1);
	}
	wait(0);
	if ((fd = open(path, O_RDONLY)) < 0)
	{
		ft_putstr_fd("open: file can not be created", 2);
		return (125);
	}
	if (fstat(fd, &sb) != 0)
		return (1); //pas de fichier
	ft_strdel((char **)buff);
	if (!(sb.st_mode & S_IRUSR))
	{
		write_error(path, 3);
		return (1); // pas droit de fichier
	}
	else if (!(S_ISREG(sb.st_mode)))
	{
		write_error(path, 2);//pas un fichier
		return (1);
	}
	int i = 0;
	char r_stock[sb.st_mode];
	if ((i = read(fd, r_stock, sb.st_size)) != sb.st_size)
	{
		printf("%d | %lld\n", i, sb.st_size);
		return (1); // read error
	}
	r_stock[i] = 0;
	(*buff) = (uint8_t *)ft_strdup(r_stock);
	//regardez que c'est bien un regular_file;
	//si read renvoie pas sb.st_size return erreur;
		//prendre les changements et les mettre dans buff
	return (0);
}
