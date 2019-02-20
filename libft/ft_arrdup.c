/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 11:07:28 by schakor           #+#    #+#             */
/*   Updated: 2018/10/16 15:21:11 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_arrdup(char **arr)
{
	char	**ret;
	size_t	i;

	i = 0;
	ret = NULL;
	if (!arr || !(ret = (char **)malloc(sizeof(*ret) * (ft_arrlen(arr) + 1))))
		return (ret);
	while (arr[i] != NULL)
	{
		ret[i] = ft_strdup(arr[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
