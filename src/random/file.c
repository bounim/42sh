/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:00:38 by emartine          #+#    #+#             */
/*   Updated: 2019/04/11 17:00:39 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "twenty_one_sh.h"
#include "random.h"

#define RAND_NB 16
#define RAND_PATH "/tmp/42sh-tmp-"

static char	u4_to_hex(uint8_t u4)
{
	return (u4 < 0xa) ? '0' + u4 : 'a' + u4 - 0xa;
}

int			random_file(char path[PATH_MAX + 1])
{
	int		rand_fd;
	uint8_t	rand_bytes[RAND_NB];
	size_t	i;

	if ((rand_fd = open("/dev/urandom", O_RDONLY)) < 0)
		return (-1);
	if (RAND_NB != read(rand_fd, rand_bytes, RAND_NB))
	{
		close(rand_fd);
		return (-1);
	}
	close(rand_fd);
	ft_memmove(path, RAND_PATH, sizeof(RAND_PATH) - 1);
	i = 0;
	while (i < RAND_NB)
	{
		path[sizeof(RAND_PATH) - 1 + i * 2] = u4_to_hex(rand_bytes[i] >> 4);
		path[sizeof(RAND_PATH) - 1 + i * 2 + 1] = u4_to_hex(rand_bytes[i]
				& 0xf);
		i++;
	}
	path[sizeof(RAND_PATH) - 1 + RAND_NB * 2] = '\0';
	return (open(path, O_RDWR | O_CREAT | O_TRUNC, 0600));
}
