/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_term_pos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 20:48:44 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/24 13:14:15 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

#define POS_BUFSIZE 32

static int	pos_sequence(void)
{
	char b;

	write(1, "\033[6n", 4);
	b = '\0';
	while (b != '\033')
	{
		if (read(0, &b, 1) <= 0)
			return (-1);
	}
	if (read(0, &b, 1) <= 0 || b != '[')
		return (-1);
	return (0);
}

static int	read_line_pos(char *buff, size_t *line)
{
	size_t	n;
	int		r;

	n = 0;
	while (n < POS_BUFSIZE - 1 && (n == 0 || buff[n - 1] != ';'))
	{
		if (read(0, buff + n, 1) <= 0)
			return (-1);
		n++;
	}
	if (n == POS_BUFSIZE - 1)
		return (-1);
	buff[n] = '\0';
	r = ft_atoi(buff);
	if (r < 1)
		return (-1);
	*line = (size_t)r - 1;
	return (0);
}

int			get_term_pos(size_t *line, size_t *col)
{
	char	buff[POS_BUFSIZE];
	size_t	n;
	int		r;

	if (pos_sequence() < 0)
		return (-1);
	if (read_line_pos(buff, line) < 0)
		return (-1);
	n = 0;
	while (n < POS_BUFSIZE - 1 && (n == 0 || buff[n - 1] != 'R'))
	{
		if (read(0, buff + n, 1) <= 0)
			return (-1);
		n++;
	}
	if (n == POS_BUFSIZE - 1)
		return (-1);
	buff[n] = '\0';
	r = ft_atoi(buff);
	if (r < 1)
		return (-1);
	*col = (size_t)r - 1;
	return (0);
}
