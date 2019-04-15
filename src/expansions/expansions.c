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

static t_argv	*add_argv(t_lexer_token *cmd) // TODO lazy add_argv in append (unless forced??)
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

	if (size == 0)
		return (0);
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

/*static uint8_t	*string_expand(t_lexer_token *cur, uint8_t *buffer, size_t *size)
{
	char	*home;
	size_t	home_len;
	uint8_t	*ret;
	size_t	i;
	size_t	j;

	(void)cur;
	(void)size;
	if (buffer != NULL) // arg word expand
	{
		i = 0;
		if (buffer[0] == '~')
		{
			if (NULL == (home = get_env_val(g_shell.envl, "HOME")))
				return (buffer);
			home_len = ft_strlen(home);
			if (NULL == (ret = malloc(home_len + *size - 1)))
				fatal_exit(SH_ENOMEM);
			ft_memmove(ret, home, home_len);
			ft_memmove(ret + home_len, buffer + 1, *size - 1);
			*size = *size - 1 + home_len;
			i = home_len;
		}
		else
			ret = buffer;
		while (i < *size - 1)
		{
			if (ret[i] == '$')
			{
				j = i + 1;
			}
			i++;
		}
		return (ret);
	}
	// else assign or redir
	return (NULL);
}*/

static size_t	tilde_arg(t_argv *argv)
{
	char	*home;

	if (NULL == (home = get_env_val(g_shell.envl, "HOME")))
		append_argv(argv, (uint8_t *)"~", 1);
	else
		append_argv(argv, (uint8_t *)home, ft_strlen(home));
	return (1);
}

static size_t	until_dollar_arg(t_argv *argv, t_lexer_token *cur,
		size_t j, size_t k)
{
	size_t	x;

	x = 0;
	while (k + x < j && cur->buffer[k + x] != '$')
		x++;
	append_argv(argv, cur->buffer + k, x);
	return (x);
}

static int		isvarchar(uint8_t ch)
{
	return (ch == '_'
			|| (ch >= '0' && ch <= '9')
			|| (ch >= 'A' && ch <= 'Z')
			|| (ch >= 'a' && ch <= 'z'));
}

static size_t	dollar_arg(t_argv **argv, t_lexer_token *cmd,
		t_lexer_token *cur, size_t j, size_t k) // FIXME 5 param
{
	size_t	x;
	size_t	s;
	size_t	e;
	char	*key;
	uint8_t	*val;

	if (k + 1 == j)
	{
		append_argv(*argv, (uint8_t *)"$", 1);
		return (1);
	}
	x = 1;
	while (k + x < j && isvarchar(cur->buffer[k + x]))
		x++;
	if (NULL == (key = malloc(x)))
		fatal_exit(SH_ENOMEM);
	ft_memmove(key, cur->buffer + k + 1, x - 1);
	key[x - 1] = '\0';
	if (NULL == (val = (uint8_t *)get_env_val(g_shell.envl, key)))
	{
		free(key);
		return (x);
	}
	s = 0;
	while (1)
	{
		while (val[s] == ' ' || val[s] == '\t')
			s++;
		if (!val[s])
			break ;
		e = s + 1;
		while (val[e] && val[e] != ' ' && val[e] != '\t')
			e++;
		//append_argv
		append_argv(*argv, val + s, e - s);
		if (!val[e])
			break ;
		// add_argv????
		*argv = add_argv(cmd); // FIXME need lazy add (on next append or add)
		s = e;
	}
	free(key);
	return (x);
}

static int		not_quoted(t_lexer_token *cmd, t_lexer_token *cur,
		t_argv **argv, size_t *i)
{
	size_t	j;
	/*uint8_t	*exp;
	size_t	explen;
	int		r;*/
	size_t	k;

	j = *i;
	while (j < cur->size && cur->buffer[j] != ' '
			&& cur->buffer[j] != '\t' && cur->buffer[j] != '\\'
			&& cur->buffer[j] != '\'' && cur->buffer[j] != '\"')
		j++;
	if (j > *i)
	{
		/*explen = j - *i;
		exp = string_expand(cur, cur->buffer + *i, &explen); // FIXME
		r = append_argv(*argv, exp, explen);
		if (exp != cur->buffer + *i)
			free(exp);
		if (r < 0)
			return (-1);*/
		k = *i;
		if (cur->buffer[*i] == '~')
			k += tilde_arg(*argv);
		while (k < j)
		{
			if (cur->buffer[k] != '$')
				k += until_dollar_arg(*argv, cur, j, k);
			else
				k += dollar_arg(argv, cmd, cur, j, k);
		}
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
