/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 13:23:10 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/10 13:23:11 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	replace_curr_charac(uint8_t input)
{
	t_char *curr;

	if (!(curr = g_shell.edit.point_char->next))
	{
		add_char_to_list(&input, 1, 0);
		clean_and_print();
		return ;
	}
	ft_memset(curr->charac, 0, curr->len);
	curr->charac[0] = input;
	curr->len = 1;
	g_shell.edit.point_char = curr;
	clean_and_print();
}

int		deal_w_input_r(uint8_t input)
{
	uint8_t touch[5];

	if (input >= 32 && input <= 126)
		replace_curr_charac(input);
	if (input == 13 || input == 10)
	{
		return_fn();
		return (1);
	}
	if (input == 27)
	{
		read(0, touch, 5);
		vi_clear_line_insert();
		return (1);
	}
	return (0);
}

void	vi_replace(void)
{
	uint8_t	input;

	while (read(0, &input, 1) >= 0)
		if (deal_w_input_r(input) == 1)
			return ;
}
