/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 16:31:34 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/04 16:31:36 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int		my_tcsetpgrp(int fd, pid_t pgrp_id)
{
	return (ioctl(fd, TIOCSPGRP, &pgrp_id));
}

pid_t	my_tcgetpgrp(int fd)
{
	int pgrp;

	pgrp = 0;
	if (ioctl(fd, TIOCGPGRP, &pgrp) < 0)
		return ((pid_t)-1);
	return ((pid_t)pgrp);
}
