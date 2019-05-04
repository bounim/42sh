/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 18:30:04 by khsadira          #+#    #+#             */
/*   Updated: 2019/05/04 19:16:59 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	word_separator(char buff)
{
	if (buff == ' ' || buff == '\n' || buff == '\t')
		return (1);
	return (0);
}

static int	cmd_separator(char buff)
{
	if (buff == '>' || buff == '<' || buff == '*' || buff == '?' || buff == '['
			|| buff == ']' || buff == '$' || buff == '|' || buff == '('
			|| buff == ')' || buff == '#' || buff == '\\' || buff == '/'
			|| buff == ';' || buff == '~' || buff == '=' || buff == '&')
		return (1);
	return (0);
}

static int	allowed_char(char buff)
{
	if (cmd_separator(buff) || word_separator(buff))
		return (0);
	return (1);
}

char	*start_replace(char *word, t_alias *alias)
{
	t_alias	*tmp;

	tmp = alias;
	while (tmp)
	{
		if (ft_strequ(word, tmp->name))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

char	*replace_alias(char *buff, t_alias *alias)
{
	int		i;
	int		n;
	char	*word;
	char	*new;

	n = 0;
	i = 0;
	while (buff[i])
	{
		if (word_separator(buff[i]))
			i++;
		else if (cmd_separator(buff[i]))
		{
			i++;
			n = 0;
		}
		else if (n == 0)
		{
			while (buff[i + n] && allowed_char(buff[i + n]))
				n++;
			word = ft_strsub(buff, i, n);
			new = start_replace(word, alias);
			ft_strdel(&word);
			word = NULL;
			if (!new)
				i += n;
		}
		else
			i++;
	}
	return (buff);
}
