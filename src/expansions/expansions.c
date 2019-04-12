/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:21:23 by kberisha          #+#    #+#             */
/*   Updated: 2019/04/09 16:54:50 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions_internal.h"

static t_argv	*add_argv(t_lexer_token *cmd)
{
	t_argv	*ret;

	if (NULL == (ret = malloc(sizeof(*ret))))
		return (NULL);
	ft_memset(ret, 0, sizeof(*ret));
	if (NULL == (ret->buffer = malloc(1)))
	{
		free(ret);
		return (NULL);
	}
	ret->buffer[0] = '\0';
	if (cmd->argv_foot)
		cmd->argv_foot->next = ret;
	else
		cmd->argv_head = ret;
	cmd->argv_foot = ret;
	cmd->argc++;
	return (ret);
}

static int		append_argv(t_argv *argv, uint8_t *buffer, size_t size)
{
	char	*new;

	if (NULL == (new = malloc(argv->len + size + 1)))
		return (-1);
	ft_memcpy(new, argv->buffer, argv->len);
	free(argv->buffer);
	argv->buffer = new;
	ft_memcpy(new + argv->len, buffer, size);
	argv->len += size;
	new[argv->len] = '\0';
	return (0);
}

/*static void		free_argv(t_argv *cur)
{
	t_argv	*prev;

	while (cur)
	{
		prev = cur;
		cur = cur->next;
		free(prev->buffer);
		free(prev);
	}
}*/

static char		*string_expand(t_lexer_token *cur, char *buffer, size_t *size)
{
	(void)cur;
	(void)size;
	if (buffer != NULL) // arg word expand
	{
		return (buffer);
	}
	// else assign or redir
	return (NULL);
}

static int		not_quoted(t_lexer_token *cmd, t_lexer_token *cur,
		t_argv **argv, size_t *i)
{
	size_t	j;
	uint8_t *exp;
	size_t explen;

	j = *i;
	while (j < cur->size && cur->buffer[j] != ' '
			&& cur->buffer[j] != '\t' && cur->buffer[j] != '\\'
			&& cur->buffer[j] != '\'' && cur->buffer[j] != '\"')
		j++;
	if (j > *i)
	{
		explen = j - *i;
		exp = (uint8_t *)string_expand(cur, (char *)cur->buffer + *i, &explen); // FIXME
		if (append_argv(*argv, exp, explen) < 0)
			return (-1);
		*i = j;
	}
	if (*i < cur->size)
	{
		if ((cur->buffer[*i] == ' ' || cur->buffer[*i] == '\t')
				&& (*argv)->len > 0)
			*argv = add_argv(cmd);
		else if (cur->buffer[*i] == '\\')
			return (1);
		else if (cur->buffer[*i] == '\'')
			return (2);
		else if (cur->buffer[*i] == '\"')
			return (3);
	}
	return (0);
}

static int		backslash(t_lexer_token *cmd, t_lexer_token *cur,
		t_argv **argv, size_t *i)
{
	(void)cmd;
	if (append_argv(*argv, cur->buffer + *i, 1) < 0)
		return (-1);
	return (0);
}

static int		simple_quote(t_lexer_token *cmd, t_lexer_token *cur,
		t_argv **argv, size_t *i)
{
	size_t	j;

	(void)cmd;
	j = *i;
	while (j < cur->size && cur->buffer[j] != '\'')
		j++;
	if (j > *i)
	{
		if (append_argv(*argv, cur->buffer + *i, j - *i) < 0)
			return (-1);
		*i = j;
	}
	return (0);
}

static int		double_quote(t_lexer_token *cmd, t_lexer_token *cur,
		t_argv **argv, size_t *i)
{
	size_t	j;
	int		quote;

	// TODO expansions
	(void)cmd;
	quote = 2;
	if (*i + 1 < cur->size && cur->buffer[*i] == '\\'
			&& cur->buffer[*i + 1] == '\"')
	{
		(*i)++;
		if (append_argv(*argv, cur->buffer + *i, 1) < 0)
			return (-1);
	}
	else
	{
		j = *i;
		while (j < cur->size && cur->buffer[j] != '\"'
				&& cur->buffer[j] != '\\')
			j++;
		if (cur->buffer[j] == '\"')
			quote = 0;
		if (j > *i)
		{
			if (append_argv(*argv, cur->buffer + *i, j - *i) < 0)
				return (-1);
			*i = j - 1;
		}
	}
	return (quote);
}

static int		(*g_exp_arg_func[])(t_lexer_token *, t_lexer_token *,
		t_argv **, size_t *) = {
	not_quoted,
	backslash,
	simple_quote,
	double_quote,
};

static int		arg_expansions(t_lexer_token *cmd, t_lexer_token *arg)
{
	t_lexer_token	*cur;
	t_argv			*argv;
	size_t			i;
	int				quote;

	cur = arg;
	while (cur)
	{
		i = 0;
		quote = 0;
		argv = add_argv(cmd);
		while (i < cur->size)
		{
			if ((quote = g_exp_arg_func[quote](cmd, cur, &argv, &i)) < 0)
				return (-1);
			i++;
		}
		cur = cur->arg_next;
	}
	return (0);
}

static int		redir_expansions(t_lexer_token *cmd, t_lexer_token *redir)
{
	t_lexer_token	*cur;

	(void)cmd;
	cur = redir;
	while (cur)
	{
		//if (cur->rtype != DLESS && cur->rtype != DLESSDASH)
		//	string_expand(cur->next, NULL, NULL); // TODO check error
		cur = cur->redir_next;
	}
	return (0);
}

static int		assign_expansions(t_lexer_token *cmd, t_lexer_token *assign)
{
	t_lexer_token	*cur;

	(void)cmd;
	cur = assign;
	while (cur)
	{
		//string_expand(cur, NULL, NULL); // TODO check error
		cur = cur->assign_next;
	}
	return (0);
}

int				command_expansions(t_lexer_token *cmd)
{
	if (!cmd || cmd->ptype != PARSER_COMMAND)
		return (0);
	if (arg_expansions(cmd, cmd->arg_head) < 0
			|| redir_expansions(cmd, cmd->redir_head) < 0
			|| assign_expansions(cmd, cmd->assign_head) < 0)
		return (-1);
	return (0);
}
