/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 15:43:51 by kberisha          #+#    #+#             */
/*   Updated: 2018/10/25 18:46:46 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	str = NULL;
	if (!s1 || !s2)
		return (NULL);
	if (!(str = (char*)malloc(sizeof(char) *
					(ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free((void*)s1);
	return (str);
}

void	fill_line(char *str, char **line)
{
	int		i;
	char	*tmp;

	if (ft_strchr(str, '\n') != NULL)
	{
		i = 0;
		while (str[i] && str[i] != '\n')
			i++;
		if (str[i] == '\n')
		{
			*line = ft_strsub(str, 0, i);
			tmp = ft_strsub(str, i + 1, ft_strlen(str) - i - 1);
			str = ft_strcpy(str, tmp);
			free(tmp);
		}
	}
	else
	{
		*line = ft_strdup(str);
		ft_bzero(str, ft_strlen(str));
	}
}

int		get_next_line(const int fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	static char	*str;
	int			ret;

	if (!line || fd < 0 || BUFF_SIZE <= 0 || (ret = read(fd, buf, 0)) == -1)
		return (-1);
	while (((ret = read(fd, buf, BUFF_SIZE)) > 0))
	{
		buf[ret] = '\0';
		if (!str)
			str = ft_strdup(buf);
		else
			str = ft_strjoin_free(str, buf);
		if (ft_strchr(str, '\n'))
			break ;
		ft_bzero(buf, BUFF_SIZE + 1);
	}
	if (ret == 0 && ft_strlen(str) == 0)
		return (0);
	else
		fill_line(str, line);
	return (1);
}
