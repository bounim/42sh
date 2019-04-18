/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:29:59 by kberisha          #+#    #+#             */
/*   Updated: 2019/04/10 18:30:19 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"
#include "execution.h"

char	*lst_to_str(t_lexer_token *head)
{
	t_lexer_token	*tmp;
	size_t			len;
	size_t			i;
	char			*str;

	tmp = head;
	len = 0;
	i = 0;
	str = NULL;
	while (tmp && tmp->ptype != PARSER_AND_OR && tmp->ptype != PARSER_SEPARATOR)
	{
		len += tmp->size + 1;
		tmp = tmp->next;
	}
	str = malloc(len);
	if (!str)
		return (NULL);
	tmp = head;
	while (tmp && tmp->ptype != PARSER_AND_OR && tmp->ptype != PARSER_SEPARATOR)
	{
		ft_memcpy(str + i, tmp->buffer, tmp->size);
		i += tmp->size + 1;
		str[i - 1] = ' ';
		tmp = tmp->next;
	}
	str[len - 1] = '\0'; //TODO verif
	return (str);
}


