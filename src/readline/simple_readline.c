/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 13:57:08 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/06 14:57:39 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void	init_simple_buff(int prompt_id)
{
	uint8_t	*simple_buff;
	int		len;

	len = get_prompt_len(prompt_id);
	if (!(simple_buff = (uint8_t*)malloc(sizeof(uint8_t) * (len + 1))))
		fatal_exit(SH_ENOMEM);
	simple_buff[len] = '\0';
	put_prompt_in_simple_buff(simple_buff, prompt_id, len);
	g_shell.edit.simple_buff = simple_buff;
	g_shell.edit.simple_buff_len = ft_u8_strlen(simple_buff);
}

static void	add_to_simple_buff(uint8_t *input)
{
	uint8_t *new;
	int		len;

	len = g_shell.edit.simple_buff_len + 1;
	if (!(new = (uint8_t*)malloc(sizeof(uint8_t) * len + 1)))
		fatal_exit(SH_ENOMEM);
	new[len] = '\0';
	ft_memmove(new, g_shell.edit.simple_buff, len);
	ft_memmove(new, input, 1);
	free(g_shell.edit.simple_buff);
	g_shell.edit.simple_buff = new;
	g_shell.edit.simple_buff_len++;
}

static void	simple_input_check(uint8_t *input)
{
	if (input[0] >= 32 && input[0] <= 126)
	{
		add_to_simple_buff(input);
		write(1, g_shell.edit.simple_buff, g_shell.edit.simple_buff_len);
	}
	if (input[0] == 10)
		simple_readline_return(g_shell.edit.simple_buff,\
				g_shell.edit.simple_buff_len);
}

static void	simple_input_controler(void)
{
	uint8_t	input[1];

	while (g_shell.edit.reading == TRUE)
	{
		if (read(0, input, 1) < 0)
			fatal_exit(SH_EINVAL);
		simple_input_check(input);
	}
}

void		simple_readline(int prompt_id)
{
	g_shell.edit.reading = TRUE;
	init_simple_buff(prompt_id);
	write(1, g_shell.edit.simple_buff, g_shell.edit.simple_buff_len);
	simple_input_controler();
}
