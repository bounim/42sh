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

char	quoted(uint8_t *buf, size_t index)
{
	size_t			i;
	enum state		state;
	char			quoted;
	uint8_t			quotechar;

	i = 0;
	quoted = 0;
	state = ST_GEN;
	while (i < index)
	{
		if (state == ST_GEN && is_quote(buf[i]))
		{
			if (buf[i] == '\\')
				state = ST_BS;
			else
				state = ST_QU;
			quotechar = buf[i];
			quoted = 1;
		}
		else if (state == ST_BS || state == ST_QU)
		{
			quoted = 1;
			if (state == ST_BS || (state == ST_QU && buf[i] == quotechar))
				state = ST_GEN;
			if (state == ST_QU && buf[i] == quotechar)
				quoted = 0;
		}
		i++;
	}
	return (quoted);
}

char	quotedstr(uint8_t *buf, size_t start, size_t len)
{
	while (start < len)
	{
		if (quoted(buf, start))
			return (1);
		start++;
	}
	return (0);
}

char	*tilde_home(void)
{
	return (get_env_val(g_shell.envl, "HOME"));
}

char	*tilde_login(t_lexer_token *tok, size_t start, size_t len)
{
	char			*login;
	char			*result;
	struct passwd	*passwd;
	size_t			pw_dir_size;

	login = NULL;
	result = NULL;
	passwd = NULL;
	if (!(login = malloc(len)))
		return (NULL);						//set une erreur de memoire qq part
	ft_memcpy(login, tok->buffer + start + 1, len - 1);
	login[len - 1] = '\0';
	if (!(passwd = getpwnam(login)))
		return (NULL);
	free(login);
	pw_dir_size = ft_strlen(passwd->pw_dir);
	result = malloc(pw_dir_size + 1);
	ft_memcpy(result, passwd->pw_dir, pw_dir_size + 1);
	return (result);
}

char	*tilde_prestamp_buffer(t_lexer_token *tok, size_t start)
{
	char	*stamp;

	stamp = NULL;
	if (start != 0)
	{
		if (!(stamp = malloc(start + 1)))
			return (NULL);
		ft_memcpy(stamp, tok->buffer, start);
		stamp[start] = '\0';
	}
	return (stamp);
}

char	*tilde_stamp_buffer(t_lexer_token *tok, size_t start, size_t len)
{
	size_t	size;
	char	*stamp;

	stamp = NULL;
	if (tok->size != len)
	{
		size = tok->size - len - start;
		if (!(stamp = malloc(size + 1)))
			return (NULL);
		ft_memcpy(stamp, tok->buffer + start + len, size);
		stamp[size] = '\0';
	}
	return (stamp);
}

int		tilde_append(t_lexer_token *tok, char *pre, char *post, char *result)
{
	size_t	pre_size;
	size_t	post_size;
	size_t	result_size;

	post_size = 0;
	pre_size = 0;
	result_size = 0;
	if (pre)
		pre_size = ft_strlen(pre);
	if (post)
		post_size = ft_strlen(post);
	if (result)
		result_size = ft_strlen(result);
	free(tok->buffer);
	tok->buffer = malloc(sizeof(uint8_t) * (result_size + pre_size + post_size));
	if (!tok->buffer)
		return (-1);
	ft_memset(tok->buffer, 0, tok->size);
	ft_memcpy(tok->buffer, pre, pre_size);
	ft_memcpy(tok->buffer + pre_size, result, result_size);
	ft_memcpy(tok->buffer + pre_size + result_size, post, post_size);
	tok->size = pre_size + result_size + post_size;
	return (0);
}

int     tilde_result(t_lexer_token *tok, size_t start, size_t len)
{
	char		*result;
	char		*pre_stamp;
	char		*post_stamp;

	result = NULL;
	pre_stamp = NULL;
	post_stamp = NULL;
	if (start != 0)
		pre_stamp = tilde_prestamp_buffer(tok, start);
	post_stamp = tilde_stamp_buffer(tok, start, len);
	if (!ft_memchr(tok->buffer, '\"', len)
			&& !ft_memchr(tok->buffer, '\'', len)
			&& !ft_memchr(tok->buffer, '\\', len))
	{
		if (len == 1)
			result = tilde_home();
		else if (!quotedstr(tok->buffer, start, len))
			result = tilde_login(tok, start, len);
		if (!result)
			return (1);
	}
	return (tilde_append(tok, pre_stamp, post_stamp, result));
}

size_t	get_tilde_prefix(t_lexer_token *token, size_t start, char assign)
{
	size_t	i;

	i = start;
	while (i < token->size && (quoted(token->buffer, i) || (token->buffer[i] != '/'
					&& (assign == 0 || token->buffer[i] != ':'))))
		i++;
	return (i - start);
}

int		tilde_word(t_lexer_token *tmp)
{
	size_t			len;

	while (tmp)
	{
		if (tmp->size >= 1 && tmp->buffer[0] == '~' && !quoted(tmp->buffer, 0))
		{
			ft_putendl("in tilde word");
			len = get_tilde_prefix(tmp, 0, 0);
			tilde_result(tmp, 0, len);
		}
		tmp = tmp->arg_next;
	}
	return (0);
}

int		tilde_redir(t_lexer_token *tmp)
{
	size_t			len;

	while (tmp)
	{
		if (tmp->size >= 1 && tmp->buffer[0] == '~' && !quoted(tmp->buffer, 0))
		{
			len = get_tilde_prefix(tmp, 0, 0);
			tilde_result(tmp, 0, len);
		}
		tmp = tmp->redir_next;
	}
	return (0);
}
int		tilde_assignement(t_lexer_token *tmp)
{
	size_t			len;
	size_t			i;

	while (tmp)
	{
		if (tmp->size >= 1)
		{
			i = tmp->assign_position + 1;
			printf("start is = %c\n", tmp->buffer[i]);
			while (i < tmp->size)
			{
				if (tmp->buffer[i] == '~' && !quoted(tmp->buffer, i)
				&& ((tmp->buffer[i - 1] && !quoted(tmp->buffer, i - 1)
				&& tmp->buffer[i - 1] == ':') || i == tmp->assign_position + 1))
				{
					len = get_tilde_prefix(tmp, i, 1);
					tilde_result(tmp, i, len);
				}
				i++;
			}
		}
		tmp = tmp->assign_next;
	}
	return (0);
}

int     tilde_expansion(t_lexer_token **root)
{
	t_lexer_token	*tmp;

	tmp = NULL;
	ft_putendl("IN TILDE");
	tilde_word((*root)->arg_head);
	ft_putendl("args");
	print_arg(*root);
	ft_putendl("END.");
	tilde_assignement((*root)->assign_head);
	ft_putendl("assignement words");
	print_assign(*root);
	ft_putendl("END.");
	if ((*root)->redir_head)
		tilde_redir((*root)->redir_head->redir_target);
	ft_putendl("redirs");
	print_redir(*root);
	ft_putendl("END.");
	return (0);
}

