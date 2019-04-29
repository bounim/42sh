/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 12:40:47 by khsadira          #+#    #+#             */
/*   Updated: 2019/04/29 12:40:47 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty_one_sh.h"

char	*rework_cdpath_arr(char *cdpath)
{
	char	*tmp;

	tmp = cdpath;
	cdpath = getcwd(NULL, 0);
	cdpath = ft_strfjoin(cdpath, "/", 0);
	cdpath = ft_strfjoin(cdpath, tmp, 2);
	return (cdpath);
}
