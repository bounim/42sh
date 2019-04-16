/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_from_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 15:28:25 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/04 16:55:45 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void		file_from_history_end(t_history *hist, int fd, char *str, char *p)
{
	if (fd > 0)
	{
		str = ft_strdup("");
		while (hist && hist->bfr)
			hist = hist->bfr;
		while (hist)
		{
			str = ft_strfjoin(str, (char *)hist->buf, 0);
			str = ft_strfjoin(str, "\n", 0);
			hist = hist->next;
		}
		if (str)
			write(fd, str, ft_strlen(str));
		ft_strdel(&str);
		ft_strdel(&p);
		close(fd);
	}
}

void		file_from_history(t_history *hist)
{
	int			fd;
	char		*str;
	char		*path;

	fd = 0;
	str = NULL;
	if (!(path = ft_strdup(get_env_val(g_shell.envl, "HISTFILE"))))
		if (!(path = ft_strjoin(get_env_val(g_shell.envl, "HOME"),
								"/.42sh_history")))
			fatal_exit(SH_ENOMEM);
	fd = open(path, O_WRONLY);
	if (fd < 0)
		fd = open(path, O_CREAT | O_WRONLY);
	file_from_history_end(hist, fd, str, path);
}