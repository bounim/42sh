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

int			is_valid_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char		*uint_to_char(uint8_t *buffer, size_t size)
{
	char	*res;

	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	ft_memcpy(res, buffer, size);
	res[size] = 0;
	return (res);
}

char		*dollar_result(t_lexer_token *tok, size_t start, size_t len)
{
	char	*result;
	char	*tmp;
	size_t	result_size;

	if (len <= 1)
		return (uint_to_char(tok->buffer, tok->size));
	printer_bin(&g_shell.out, tok->buffer, tok->size);
	printer_endl(&g_shell.out);
	printer_flush(&g_shell.out);
	if (!(tmp = malloc(len + 1)))
		return (NULL);
	ft_memcpy(tmp, tok->buffer + start, len);
	tmp[len] = '\0';
	result = get_env_val(g_shell.envl, tmp);
	free(tmp);
	result_size = ft_strlen(result);
	if (!(tmp = malloc(result_size + tok->size - len)))
		return (NULL);
	ft_memset(tmp, 0, result_size + tok->size - len);
	ft_memcpy(tmp, tok->buffer, start - 1);
	ft_memcpy(tmp + start - 1, result, result_size);
	ft_memcpy(tmp + result_size + start - 1, tok->buffer + start + len,
			tok->size - start - len);
	return (tmp);
}

size_t		expr_lenght(uint8_t *buffer, size_t size, size_t start)
{
	size_t	i;

	i = start;
	if (ft_isdigit(buffer[i]))
		return (0);
	while (i < size && (buffer[i] != '}' || quoted(buffer, i)) && is_valid_char(buffer[i]))
		i++;
	printf("len = %zu\n" , i - start + 1);
	return (i - start);
}

size_t		expr_start(uint8_t *buffer, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && buffer[i] != '$')
		i++;
	if (buffer[i] == '$')
	{
		ft_putendl("l000ol");
		i++;
	}
	while (i < size && buffer[i] == '{')
		i++;
	return (i);
}

void	print_tab(char **t)
{
	int i = 0;
	while (t[i])
		ft_putendl(t[i++]);
}

int		add_argv(t_lexer_token *root, char *argv)
{
	t_argv	*new;
	size_t	argsize;

	printf("argv =%s\n", argv);
	if (!(new = malloc(sizeof(*new))))
		return (-1);
	ft_memset(new, 0, sizeof(*new));
	argsize = ft_strlen(argv);
	if (!(new->buffer = malloc(argsize + 1)))
	{
		free(new);
		return (-1);
	}
	ft_memcpy(new->buffer, argv, argsize + 1);
	if (root->argv_foot)
		root->argv_foot->next = new;
	else
		root->argv_head = new;
	root->argv_foot = new;
	root->argc++;
	return (0);
}

int		parameter_expansion(t_lexer_token *root)
{
	t_lexer_token	*tmp;
	size_t len, start;

	tmp = root->arg_head;
	start = 0;
	len = 0;
	while (tmp)										//gerer $PWD$HOME
	{
		if (ft_memchr(tmp->buffer, '$', tmp->size))
		{
			start = expr_start(tmp->buffer, tmp->size);
			len = expr_lenght(tmp->buffer, tmp->size, start);
			add_argv(root, dollar_result(tmp, start, len));
		}
		tmp = tmp->arg_next;
	}
	return (0);
}
