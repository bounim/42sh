/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonical_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 16:00:46 by emartine          #+#    #+#             */
/*   Updated: 2018/10/30 16:00:48 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

int			canonical_path(char *result, char *workdir, char *input)
{
	size_t	i;
	int		slash;
	size_t	dot;
	size_t	word_length;
	size_t	diff;

	if (input[0] == '\0')
	{
		ft_strncpyz(result, workdir, PATH_MAX + 1);
		return (0);
	}
	if (input[0] != '/')
	{
		i = ft_stpncpyz(result, workdir, PATH_MAX + 1) - result;
		if (i >= PATH_MAX)
			return (-1);
		result[i++] = '/';
	}
	else
	{
		result[0] = '/';
		input++;
		i = 1;
	}
	slash = 1;
	dot = 0;
	word_length = 0;
	while (1)
	{
		if (word_length > 0 && (*input == '/' || *input == '\0')) // copy word
		{
			if (*input == '/')
				input++; // ending slash
			if (i + word_length + 1 > PATH_MAX)
				return (-1);
			ft_memcpy(result + i, input - word_length, word_length);
			i += word_length;
			result[i++] = '/';
			if (*input == '\0')
				break ;
			word_length = 0;
			slash = 1;
		}
		else if (*input == '\0')
			break ;
		else if (*input == '/')
		{
			if (slash) // remove useless slashes
			{
				while (*input == '/')
					input++;
				slash = 0;
			}
			else if (dot == 1) // useless /./
			{
				// do nothing?
			}
			else if (dot == 2) // .. (tricky)
			{
				// find previous word start?
				// nb: /../ => /
				// assert result[i - 1] == '/'
				if (i == 1) // /../ => /
				{
					// do nothing
				}
				i--;
				diff = 1;
				// assert result[0] == '/'
				while (result[i - 1] != '/')
				{
					i--;
					diff++;
				}
				ft_memset(result + i, 0, diff); // remove previous directory
			}
			dot = 0;
		}
		else if (word_length == 0 && *input == '.')
			dot++;
		else
		{
			if (dot)
			{
				word_length += dot;
				dot = 0;
			}
			word_length++;
		}
		input++;
	}
	if (i > 1 && result[i - 1] == '/')
		result[i - 1] = '\0'; // remove ending slash
	return (0);
}
