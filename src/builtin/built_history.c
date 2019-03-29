/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:28:52 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/29 16:14:01 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int			built_history(char **arg, t_history **hist)
{
	int		len;

	if ((len = ft_arrlen(arg)) >= 1)
	{
		print_historyl(*hist);
		return (0);
	}
	return (1);
}
