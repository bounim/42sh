/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_conditions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:52:32 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/02 19:10:40 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int	copy_current_word_start_conditions(t_char *curr)
{
	if (!curr->next || (curr->next && (curr->next->charac[0] == ' '
	|| curr->next->charac[0] == '\n' || curr->next->charac[0] == '\t'
	|| ft_memcmp(curr->next->charac, NBSP, 2) == 0)))
		return (-1);
	return (1);
}

int	copy_current_word_begin_conditions(t_char *curr)
{
	if (curr->prev->is_prompt == 0 && (curr->prev->charac[0] != ' '
	&& curr->prev->charac[0] != '\n' && curr->prev->charac[0] != '\t'
	&& ft_memcmp(curr->prev->charac, NBSP, 2) != 0))
		return (1);
	return (-1);
}

int	copy_current_word_end_conditions(t_char *curr)
{
	if (curr->next && (curr->next->charac[0] != ' '
	&& curr->next->charac[0] != '\n'
	&& curr->next->charac[0] != '\t'
	&& ft_memcmp(curr->next->charac, NBSP, 2) != 0))
		return (1);
	return (-1);
}
