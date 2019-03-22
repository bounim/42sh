/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_from_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 15:28:25 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/22 15:39:46 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void		file_from_history(char *path, t_history *hist)
{
	int			fd;
	char		*str;

	path = ft_strfjoin(path, "/.21sh_history", 0);
	fd = open(path, O_WRONLY);
	if (fd < 0)
		fd = open(path, O_CREAT | O_WRONLY);
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
		ft_strdel(&path);
		close(fd);
	}
}
