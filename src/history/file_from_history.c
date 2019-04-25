/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_from_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 15:28:25 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/25 16:03:13 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void	file_from_history_end(t_history *hist, int fd, char *str)
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
		close(fd);
	}
	ft_strdel(&str);
}

void		file_from_history(t_history *hist)
{
	int			fd;
	char		*str;
	char		*path;

	fd = 0;
	str = NULL;
	path = NULL;
	if (!(path = get_env_val(g_shell.envl, "HISTFILE")))
		return ;
	fd = open(path, O_WRONLY);
	if (fd < 0)
		fd = open(path, O_CREAT | O_WRONLY);
	file_from_history_end(hist, fd, str);
}
