/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 22:38:35 by kberisha          #+#    #+#             */
/*   Updated: 2019/03/14 22:38:38 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

size_t		expr_lenght(uint8_t *buffer, size_t size, size_t start)
{
	size_t	i;

	i = start;
	while (i < size && buffer[i] != '}')
		i++;
	return (i - start);
}

size_t		expr_start(uint8_t *buffer, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && buffer[i] != '$')
		i++;
	printf("i is = %zu\n", i);
	if (i < size - 1 && buffer[i] == '{')
		return (i + 2);
	return (i + 1);
}

int		parameter_expansion(t_lexer_token **root)
{
	t_lexer_token	*tmp;
	size_t len, start;

	tmp = (*root)->arg_head;
	start = 0;
	len = 0;
	while (tmp)
	{
		if (ft_memchr(tmp->buffer, '$', tmp->size))
		{
			ft_putendl("ayooo");
			start = expr_start(tmp->buffer, tmp->size);
			len = expr_lenght(tmp->buffer, tmp->size, start);
			printf("start = %zu & len = %zu\n", start, len);
		}
		tmp = tmp->arg_next;
	}
	return (0);
}
