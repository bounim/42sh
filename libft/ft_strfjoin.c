/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:18:00 by schakor           #+#    #+#             */
/*   Updated: 2019/03/06 15:59:46 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strfjoin(char *s1, char *s2, int opt)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	if (opt == 0)
		free(s1);
	else if (opt == 1)
		free(s2);
	else if (opt == 2)
	{
		free(s1);
		free(s2);
	}
	return (ret);
}
