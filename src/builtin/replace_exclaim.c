/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_exclaim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:46:49 by khsadira          #+#    #+#             */
/*   Updated: 2019/03/29 17:39:48 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int		concat_exclaim(char *line, int i)
{
	int	j;

	j = i + 1;
	if (!line[j])
		return (0);
	else if (line[j] == '!')
		j++;
	else if (ft_isalpha(line[j]))
		while (ft_isalnum(line[j]))
			j++;
	else if (ft_isdigit(line[j]) || line[j] == '-')
	{
		if (line[j] == '-')
			j++;
		while (ft_isdigit(line[j]))
			j++;
	}
	return (j - 1);
}

static char		*free_exclaim(char *s1, char *s2, char *s3, char *s4)
{
	ft_strdel(&s1);
	ft_strdel(&s2);
	ft_strdel(&s3);
	ft_strdel(&s4);
	return (NULL);
}

static void		print_special_error(char *line, int i)
{
	ft_putstr_fd("event not found: ", 2);
	ft_putendl_fd(line + i, 2);
	ft_strdel(&line);
}

char			*replace_exclaim(char *line, t_history *hist,
		char *bfr, char *next)
{
	int		i;
	int		j;
	char	*concat;
	char	*tmp;

	while ((i = ft_strichr(line, '!')) != -1)
	{
		if ((j = concat_exclaim(line, i)) == 0)
			return (free_exclaim(line, NULL, NULL, NULL));
		if (!(concat = ft_strsub(line, i, j - i + 1))
				|| !(bfr = ft_strsub(line, 0, i))
				|| !(tmp = find_exclaim(concat, hist))
				|| !(next = ft_strsub(line, j + 1, ft_strlen(line) - j)))
		{
			print_special_error(line, i);
			return (free_exclaim(concat, bfr, tmp, next));
		}
		ft_strdel(&line);
		line = ft_strfjoin(bfr, tmp, 0);
		line = ft_strfjoin(line, next, 2);
		ft_strdel(&concat);
	}
	return (line);
}
