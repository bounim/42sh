/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 23:03:00 by schakor           #+#    #+#             */
/*   Updated: 2019/01/30 19:19:19 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void			rl_get_prompt(t_rl *rl)
{
	char	*cwd;
	char	buff[4097];
	int		i;
	int		len;
	char	*tmp;

	tmp = NULL;
	if ((cwd = getcwd(buff, 4096)))
	{
		len = ft_strlen(cwd);
		i = len;
		while (i > 0 && cwd[i] != '/')
			i--;
		if (cwd[i] == '/' && ft_strlen(cwd) != 1)
			i++;
		tmp = ft_strsub(cwd, i, len - i);
	}
	rl->len_prompt = 3;
	rl->prompt = ft_strdup("<");
	if (tmp)
		rl->prompt = ft_strfjoin(rl->prompt, tmp, 0);
	rl->prompt = ft_strfjoin(rl->prompt, "> ", 0);
	if (tmp)
		rl->len_prompt += ft_strlen(tmp);
	free(tmp);
}

void			rl_display_prompt(const char *prompt)
{
	ft_putstr(prompt);
}
