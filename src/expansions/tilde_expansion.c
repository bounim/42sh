/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:11:47 by kberisha          #+#    #+#             */
/*   Updated: 2019/03/11 16:11:48 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

size_t  tilde_prefix_len(t_buffer *buffer, size_t start, uint8_t assign)
{
	size_t  len;

	len = start;
	if (buffer->buf[start] == '~')
	{
		while (len < buffer->size && buffer->buf[len] != '/' && (buffer->buf[len] != ':' || assign == 0)
				&& !is_quote(buffer->buf[len])) //rajouter state quoted
			len++;
	}
	printf("len - start = %zu\n", len - start);
	return (len - start);
}

char	*get_env(char *elem)
{
	size_t	i;
	size_t	j;
	char	*tmp;
	extern char **environ; // XXX

	i = 0;
	j = ft_strlen(elem);
	tmp = NULL;
	while (environ[i])
	{
		if (!ft_memcmp(environ[i], elem, j) && environ[i][j] == '=')
		{
			tmp = environ[i] + j + 1;
			break ;
		}
		i++;
	}
	return (*tmp != '\0' ? tmp : NULL);
}

char	*tilde_home(void)
{
	char	*result;


	result = NULL;
	ft_putendl("in tilde home");
	if (!(result = get_env("HOME")))
		return (NULL);
	return (result);
}

char	*tilde_login(size_t tilde_prefix_len, t_buffer *buffer, size_t start)
{
	char			*login;
	char			*result;
	struct passwd	*passwd;
	size_t			pw_dir_size;

	login = NULL;
	result = NULL;
	passwd = NULL;
	if (!(login = malloc(tilde_prefix_len)))
		return (NULL);												//set une erreur de memoire qq part
	ft_memcpy(login, buffer->buf + start + 1, tilde_prefix_len - 1);
	login[tilde_prefix_len - 1] = '\0';
	if (!(passwd = getpwnam(login)))
		return (NULL);
	free(login);
	pw_dir_size = ft_strlen(passwd->pw_dir);
	result = malloc(pw_dir_size + 1);
	ft_memcpy(result, passwd->pw_dir, pw_dir_size + 1);
	return (result);
}

char	*tilde_prestamp_buffer(t_buffer *buffer, size_t start)
{
	char	*stamp;

	stamp = NULL;
	if (start != 0)
	{
		if (!(stamp = malloc(start + 1)))
			return (NULL);
		ft_memcpy(stamp, buffer->buf, start);
		stamp[start] = '\0';
	}
	return (stamp);
}

char	*tilde_stamp_buffer(t_buffer *buffer, size_t tilde_prefix_len, size_t start)
{
	size_t	size;
	char	*stamp;

	stamp = NULL;
	if (buffer->size != tilde_prefix_len)
	{
		size = buffer->size - tilde_prefix_len - start;
		if (!(stamp = malloc(size + 1)))
			return (NULL);
		ft_memcpy(stamp, buffer->buf + start + tilde_prefix_len, size);
		stamp[size] = '\0';
	}
	return (stamp);
}

int		tilde_append(t_buffer *buffer, char *pre_stamp, char *post_stamp, char *result)
{
	size_t	pre_stamp_size;
	size_t	post_stamp_size;
	size_t	result_size;

	post_stamp_size = 0;
	pre_stamp_size = 0;
	result_size = 0;
	if (pre_stamp)
		pre_stamp_size = ft_strlen(pre_stamp);
	if (post_stamp)
		post_stamp_size = ft_strlen(post_stamp);
	if (result)
		result_size = ft_strlen(result);
	free(buffer->buf);
	buffer->buf = malloc(sizeof(uint8_t) * (result_size + pre_stamp_size + post_stamp_size));
	if (!buffer->buf)
		return (-1);
	ft_memset(buffer->buf, 0, buffer->size);
	ft_memcpy(buffer->buf, pre_stamp, pre_stamp_size);
	ft_memcpy(buffer->buf + pre_stamp_size, result, result_size);
	ft_memcpy(buffer->buf + pre_stamp_size + result_size, post_stamp, post_stamp_size);
	buffer->size = pre_stamp_size + result_size + post_stamp_size;
	return (0);
}

int     tilde_result(t_buffer *buffer, size_t start, size_t tilde_prefix_len)
{
	char		*result; //ou uint8_t ??
	char		*pre_stamp;
	char		*post_stamp;

	result = NULL;
	pre_stamp = NULL;
	post_stamp = NULL;
	if (start != 0)
		pre_stamp = tilde_prestamp_buffer(buffer, start);
	post_stamp = tilde_stamp_buffer(buffer, tilde_prefix_len, start);
	if (!ft_memchr(buffer->buf, tilde_prefix_len, '\"') && !ft_memchr(buffer->buf, tilde_prefix_len, '\'')
			&& !ft_memchr(buffer->buf, tilde_prefix_len, '\\'))
	{
		if (tilde_prefix_len == 1)
			result = tilde_home();
		else
			result = tilde_login(tilde_prefix_len, buffer, start);
		if (!result)
			return (1);
	}
	return (tilde_append(buffer, pre_stamp, post_stamp, result));
}

int     do_tilde_redir(t_redir *redir_head)
{
	t_redir  *tmp;
	size_t  len;

	tmp = redir_head;
	while (tmp)
	{
		if (tmp->buffer->size >= 1 && tmp->buffer->buf[0] == '~')
		{
			len = tilde_prefix_len(tmp->buffer, 0, 0);
			tilde_result(tmp->buffer, 0, len);
			tmp->tilded = 1;
		}
		tmp = tmp->next;
	}
	return (0);
}

int     do_tilde_arg(t_word *arg_head)
{
	t_word  *tmp;
	size_t  len;

	tmp = arg_head;
	while (tmp)
	{
		if (tmp->buffer->size >= 1 && tmp->buffer->buf[0] == '~')
		{
			len = tilde_prefix_len(tmp->buffer, 0, 0);
			tilde_result(tmp->buffer, 0, len);
			tmp->tilded = 1;
		}
		tmp = tmp->next;
	}
	return (0);
}

int		do_tilde_assign(t_word *assign_head)
{
	t_word	*tmp;
	size_t	len;
	size_t	i;


	tmp = assign_head;
	while (tmp)
	{
		if (tmp->buffer->size >= 1)
		{
			i = 0;
			while (i < tmp->buffer->size)
			{
				if (tmp->buffer->buf[i] == '~' && tmp->buffer->buf[i - 1]
					&& (tmp->buffer->buf[i - 1] == '=' || tmp->buffer->buf[i - 1] == ':'))
				{
					len = tilde_prefix_len(tmp->buffer, i, 1);
					printf("buf[%zu] = %c\n", i, tmp->buffer->buf[i]);
					tilde_result(tmp->buffer, i, len);
				}
				i++;
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int     tilde_expansion(t_parser_node **head)
{
	t_word   *tmp;
	t_redir	*redir;

	ft_putendl("DOING EXPANSIONS");
	do_tilde_arg((*head)->arg_head);
	do_tilde_assign((*head)->assign_head);
	do_tilde_redir((*head)->redir_head);
	ft_putendl("IN TILDE EXPANSIONS\n");
	tmp = (*head)->arg_head;
	ft_putendl("\nPRINTING EXP ARGS");
	while (tmp)
	{
		print_token(tmp->buffer->buf, tmp->buffer->size);
		tmp = tmp->next;
	}
	tmp = (*head)->assign_head;
	ft_putendl("\nPRINTING EXP ASSIGNS");
	while (tmp)
	{
		print_token(tmp->buffer->buf, tmp->buffer->size);
		tmp = tmp->next;
	}
	redir = (*head)->redir_head;
	ft_putendl("\nPRINTING EXP REDIRS");
	while (redir)
	{
		print_token(redir->buffer->buf, redir->buffer->size);
		redir = redir->next;
	}
	// do_tilde_assign((*head)->assign_head);
	// do_tilde_redir((*head)->redir_head);
	return (0);
}

void	do_expansions(t_parser_node *tree)
{
	if (!tree)
		return ;
	else
	{
		do_expansions(tree->right);
		if (tree->type == PARSER_COMMAND)
			// print_token(tree->arg_head->buf, tree->arg_head->size);
			tilde_expansion(&tree);
		do_expansions(tree->left);
	}
}