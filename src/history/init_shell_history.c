/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_history.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <schakor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 14:41:06 by schakor           #+#    #+#             */
/*   Updated: 2019/02/18 16:54:08 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static uint8_t		*get_histfile_content()
{
	uint8_t			*ret;
	uint8_t			buf[BUFF_SIZE + 1];
	int				fd;
	char			*histpath;
	int				rd;

	if (!(histpath = ft_strjoin(get_env_val(g_shell.envl, "HOME"),
								"/.21sh_history")))
		fatal_exit(SH_ENOMEM);
	if (((fd = open(histpath, O_RDONLY)) < 0) || read(fd, buf, 0) < 0)
		return (NULL);
	if (!(ret = ft_u8_strnew(0)))
		fatal_exit(SH_ENOMEM);
	while ((rd = read(fd, buf, BUFF_SIZE)))
	{
		buf[rd] = '\0';
		ret = ft_u8_strfjoin(ret, buf, 0);
	}
	if (close(fd) == -1)
		fatal_exit(SH_EINVAL);
	return (ret);
}

static void			init_bufvar(t_bufvar *bufvar, uint8_t *ustr)
{
	bufvar->i_buf = ft_u8_strlen(ustr);
	bufvar->len_buf = ft_u8_strlen(ustr);
	bufvar->i_char = ft_wslen((char *)ustr);
	bufvar->len_char = ft_wslen((char *)ustr);
	bufvar->len_tot = ft_u8_strlen(ustr);
}

static t_history	*parse_histfile_content(uint8_t *cont)
{
	t_history		*ret;
	t_history		*new;
	t_bufvar		bufvar;
	uint8_t 		**cont_arr;
	size_t 			i;

	if (!(cont_arr = ft_u8_strsplit(cont, (uint8_t )'\n')))
		return (NULL);
	i = 0;
	ret = NULL;
	while (cont_arr[i] != NULL)
	{
		g_shell.history_size++;
		init_bufvar(&bufvar, cont_arr[i]);
		new = rl_new_hist(cont_arr[i], bufvar);
		ret = rl_add_hist(ret, new);
		i++;
	}
	ft_arrdel((char **)cont_arr);
	return (ret);
}

t_history			*init_shell_history(void)
{
	t_history		*ret;
	uint8_t 		*cont;

	if (!(cont = get_histfile_content()))
		return (NULL);
	ret = parse_histfile_content(cont);
	return (ret);
}
