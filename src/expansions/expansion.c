/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:21:23 by kberisha          #+#    #+#             */
/*   Updated: 2019/04/03 16:21:25 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

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

static int		arg_expansions(t_lexer_token *cmd, t_lexer_token *arg)
{
	t_lexer_token	*cur;
	t_argv			*argv;
	size_t			i;
	size_t			j;
	int				quote;

	cur = arg;
	while (cur)
	{
		i = 0;
		quote = 0;
		argv = add_argv(cmd);
		while (i < cur->size)
		{
			if (quote == 0)
			{
				// TODO expansions
				j = i;
				while (j < cur->size && cur->buffer[j] != ' '
						&& cur->buffer[j] != '\t' && cur->buffer[j] != '\\'
						&& cur->buffer[j] != '\'' && cur->buffer[j] != '\"')
					j++;
				if (j > i)
				{
					if (append_argv(argv, cur->buffer + i, j - i) < 0)
						return (-1);
					i = j;
				}
				if (i < cur->size)
				{
					if ((cur->buffer[i] == ' ' || cur->buffer[i] == '\t')
							&& argv->len > 0)
						argv = add_argv(cmd);
					else if (cur->buffer[i] == '\\')
						quote = 1;
					else if (cur->buffer[i] == '\'')
						quote = 2;
					else if (cur->buffer[i] == '\"')
						quote = 3;
				}
			}
			else if (quote == 1)
			{
				if (append_argv(argv, cur->buffer + i, 1) < 0)
					return (-1);
				quote = 0;
			}
			else if (quote == 2)
			{
				j = i;
				while (j < cur->size && cur->buffer[j] != '\'')
					j++;
				if (j > i)
				{
					if (append_argv(argv, cur->buffer + i, j - i) < 0)
						return (-1);
					i = j;
				}
				quote = 0;
			}
			else
			{
				// TODO expansions
				if (i + 1 < cur->size && cur->buffer[i] == '\\'
						&& cur->buffer[i + 1] == '\"')
				{
					i++;
					if (append_argv(argv, cur->buffer + i, 1) < 0)
						return (-1);
				}
				else
				{
					j = i;
					while (j < cur->size && cur->buffer[j] != '\"'
							&& cur->buffer[j] != '\\')
						j++;
					if (cur->buffer[j] == '\"')
						quote = 0;
					if (j > i)
					{
						if (append_argv(argv, cur->buffer + i, j - i) < 0)
							return (-1);
						i = j - 1;
					}
				}
			}
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
		cur = cur->assign_next;
	}
	return (0);
}

static int		command_expansions(t_lexer_token *cmd)
{
	if (arg_expansions(cmd, cmd->arg_head) < 0
			|| redir_expansions(cmd, cmd->redir_head) < 0
			|| assign_expansions(cmd, cmd->assign_head) < 0)
		return (-1);
	return (0);
}

int				do_expansions(t_lexer *lex)
{
	if (!lex->expansion_i)
		lex->expansion_i = lex->head;
	else
		lex->expansion_i = lex->expansion_i->next;
	while (lex->expansion_i && lex->expansion_i->ptype != PARSER_SEPARATOR)
	{
		if (lex->expansion_i->ptype == PARSER_COMMAND)
		{
			if (command_expansions(lex->expansion_i) < 0)
				return (-1);
		}
		lex->expansion_i = lex->expansion_i->next;
	}
	return (0);
}
