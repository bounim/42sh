/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 01:48:37 by kberisha          #+#    #+#             */
/*   Updated: 2017/11/24 15:30:22 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char const *s, int fd)
{
	size_t	i;
	char	*ss;

	i = 0;
	if (s)
	{
		ss = (char*)s;
		while (ss[i])
		{
			ft_putchar_fd(ss[i], fd);
			i++;
		}
	}
}
