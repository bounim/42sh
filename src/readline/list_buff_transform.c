/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_buff_transform.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 14:14:00 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/04 14:57:19 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

t_char		*find_first_non_prompt(t_char *head)
{
	while (head && head->is_prompt == 1)
		head = head->next;
	return (head);
}

t_char		*skip_prompt(t_char *head)
{
	while (head && head->is_prompt == 1)
		head = head->next;
	return (head);
}

int			get_buf_size(t_char *head, t_char *end)
{
	int	buff_size;

	buff_size = 0;
	while (head != end)
	{
		buff_size += head->len;
		head = head->next;
	}
	return (buff_size);
}

uint8_t		*list_to_buff_print(t_char *curr, t_char *end)
{
	uint8_t		*ret;
	int			buff_size;
	int			i;

	buff_size = get_buf_size(curr, end);
	if (!(ret = (uint8_t*)malloc(sizeof(uint8_t) * (buff_size + 1))))
	{
		fatal_exit(SH_ENOMEM);
		return (NULL);
	}
	ret[buff_size] = '\0';
	i = 0;
	while (curr != end)
	{
		ft_memmove(ret + i, curr->charac, curr->len);
		i += curr->len;
		curr = curr->next;
	}
	return (ret);
}
