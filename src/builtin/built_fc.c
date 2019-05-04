/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 12:09:03 by aguillot          #+#    #+#             */
/*   Updated: 2019/05/04 16:06:06 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	get_range_buff_len(int start, int end, t_history *curr)
{
	int len;

	len = 0;
	while (start <= end && curr)
	{
		len += ft_u8_strlen(curr->buf) + 1;
		start++;
		curr = curr->next;
	}
	return (len);
}

static int	fc_build_buff(uint8_t **buff, t_history *history, int range[2])
{
	int	len;
	int	start;

	start = range[0];
	if (!(history = find_specific_hist_line(range[0], find_first_hist_line())))
		return (-1);
	len = get_range_buff_len(start, range[1], history);
	if (!(*buff = (uint8_t*)malloc(sizeof(uint8_t) * (len + 1))))
		return (-1);
	*buff = ft_memset(*buff, 0, len);
	len = 0;
	start = range[0];
	if (!(history = find_specific_hist_line(range[0], find_first_hist_line())))
		return (-1);
	while (start <= range[1] && history)
	{
		ft_memmove((*buff) + len, history->buf, ft_u8_strlen(history->buf));
		len += ft_u8_strlen(history->buf) + 1;
		ft_memmove((*buff) + len - 1, "\n", 1);
		start++;
		history = history->next;
	}
	return (len);
}

static char	*find_fc_editor(char **av, t_envl *envl, int opts_e)
{
	char *editor;

	if (opts_e)
	{
		if (!(*av))
		{
			write_error("fc", "-e: option requires an argument");
			return (NULL);
		}
		editor = *av;
		return (editor);
	}
	if (!(editor = get_env_val(envl, "FCEDIT")))
		if (!(editor = get_env_val(envl, "EDITOR")))
			editor = "ed";
	return (editor);
}

static int	fc_controler(char **av, int fc_range[2], int fc_opts[5],
		t_envl *envl)
{
	uint8_t	*buff;
	int		len;
	char	*editor;

	if (fc_opts[L])
	{
		if (!fc_opts[R])
			print_fc_list(fc_opts, fc_range);
		else
			print_fc_list_reverse(fc_opts, fc_range);
	}
	else
	{
		if (!(editor = find_fc_editor(av, envl, fc_opts[E])))
			return (1);
		buff = NULL;
		if ((len = fc_build_buff(&buff, g_shell.hist.history, fc_range)) == -1)
			return (1);
		if (!fc_opts[S])
			if (fc_modification(&buff, envl, editor, len) > 0)
				return (125);
		//return (fc_exec(buff, g_shell.envl));
	}
	return (0);
}

int			built_fc(char **av, t_envl *envl)
{
	int fc_opts[5];
	int index;
	int fc_range[2];

	if ((index = check_fc_opts(av, fc_opts)) == -1)
		return (1);
	if (build_fc_range(av + index, fc_range, fc_opts))
		return (1);
	if (check_fc_range(fc_range) == OUT_OF_RANGE)
		return (1);
	if (fc_controler(av + index, fc_range, fc_opts, envl))
		return (1);
	return (0);
}
