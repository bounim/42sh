/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_term_pos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 20:48:44 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/09 20:48:45 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int	get_term_pos(size_t *line, size_t *col)
{
	char	buff[32];
	size_t	n;
	int		r;

	write(1, "\033[6n", 4);
	buff[0] = '\0';
	while (buff[0] != '\033')
	{
		if (read(0, buff, 1) <= 0)
			return (-1);
	}
	if (read(0, buff, 1) <= 0 || buff[0] != '[')
		return (-1);
	n = 0;
	while (n < sizeof(buff) - 1 && (n == 0 || buff[n - 1] != ';'))
	{
		if(read (0, buff + n, 1) <= 0)
			return (-1);
		n++;
	}
	if (n == sizeof(buff) - 1)
		return (-1);
	buff[n] = '\0';
	r = atoi(buff);
	if (r < 1)
		return (-1);
	*line = (size_t)r - 1;
	n = 0;
	while (n < sizeof(buff) - 1 && (n == 0 || buff[n - 1] != 'R'))
	{
		if(read (0, buff + n, 1) <= 0)
			return (-1);
		n++;
	}
	if (n == sizeof(buff) - 1)
		return (-1);
	buff[n] = '\0';
	r = atoi(buff);
	if (r < 1)
		return (-1);
	*col = (size_t)r - 1;
	return (0);
}