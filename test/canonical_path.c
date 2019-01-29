/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonical_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:52:01 by emartine          #+#    #+#             */
/*   Updated: 2019/01/28 16:52:13 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "test.h"
#include "libft.h"
#include "utils.h"

static t_test *const g_test[] = {
	&((t_test){"/work/dir", "", "/work/dir"}),
	&((t_test){"/work/dir", "f", "/work/dir/f"}),
	&((t_test){"/work/dir", "f/g", "/work/dir/f/g"}),
	&((t_test){"/work/dir", "f/g/", "/work/dir/f/g"}),
	&((t_test){"/work/dir", "/r", "/r"}),
	&((t_test){"/work/dir", "/", "/"}),
	&((t_test){"/work/dir", "//", "/"}),
	&((t_test){"/work/dir", "//r", "/r"}),
	&((t_test){"/work/dir", "//r//s", "/r/s"}),
	&((t_test){"/work/dir", ".", "/work/dir"}),
	&((t_test){"/work/dir", "./", "/work/dir"}),
	&((t_test){"/work/dir", "./d", "/work/dir/d"}),
	&((t_test){"/work/dir", "./d/", "/work/dir/d"}),
	&((t_test){"/work/dir", "..", "/work"}),
	&((t_test){"/work/dir", "../", "/work"}),
};

static int	test(t_printer_handle *out, size_t t)
{
	char	result[PATH_MAX + 1];
	char	workdir[PATH_MAX + 1];
	int		r;

	ft_memset(result, '\0', sizeof(result));
	ft_strncpyz(workdir, g_test[t]->workdir, sizeof(workdir));
	printer_ulong(out, t);
	printer_bin(out, ": canonical_path(", 17);
	printer_str(out, workdir);
	printer_bin(out, ", ", 2);
	printer_str(out, g_test[t]->input);
	printer_bin(out, ") == ", 5);
	printer_str(out, g_test[t]->result);
	printer_bin(out, " >> ", 4);
	if ((r = canonical_path(result, workdir, g_test[t]->input)))
	{
		printer_int(out, r);
		printer_bin(out, " (", 2);
		printer_str(out, result);
		printer_bin(out, ")", 1);
		return (1);
	}
	if (ft_strcmp(result, g_test[t]->result) != 0)
	{
		printer_str(out, result);
		return (1);
	}
	printer_bin(out, "SUCCESS", 7);
	return (0);
}

int			main(void)
{
	size_t				t;
	t_printer_handle	out;
	int					r;

	printer_init(&out, 1);
	t = 0;
	r = 0;
	while (t < sizeof(g_test) / sizeof(g_test[0]))
	{
		if (test(&out, t))
			r++;
		printer_endl(&out);
		t++;
	}
	printer_flush(&out);
	return (r);
}
