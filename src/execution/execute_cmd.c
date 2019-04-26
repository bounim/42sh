/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:47:32 by kberisha          #+#    #+#             */
/*   Updated: 2019/04/26 13:45:14 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "twenty_one_sh.h"
#include "execution.h"
#include "expansions.h"

char	**arg_to_argv(t_lexer_token *cmd)
{
	size_t			i;
	t_lexer_token	*cur;
	char			**av;

	if (NULL == (av = malloc((cmd->arg_nb + 1) * sizeof(*av))))
		return (NULL);
	i = 0;
	cur = cmd->arg_head;
	while (i < cmd->arg_nb)
	{
		av[i] = (char *)cur->buffer;
		i++;
		cur = cur->arg_next;
	}
	av[cmd->arg_nb] = NULL;
	return (av);
}

int		execute_simple_command(t_lexer_token *cmd) //ajouter exit status ds launch job ou end_job
{
	t_proc			*new_proc;
	t_job			*new_job;

	new_job = NULL;
	if (!cmd ||  cmd->ptype != PARSER_COMMAND || command_expansions(cmd) < 0)
		return (-1);
	new_proc = create_proc(&new_job, cmd);
	execute_assign_list(cmd, new_proc);        //0 = & (background)
	launch_job(new_job); //1 == foreground
	return (0);
}

int		execute_pipe(t_lexer_token *pipe_seq)
{
	t_lexer_token	*cur;
	t_job			*new_job;
	t_proc			*new_proc;

	new_job = NULL;
	if (!pipe_seq)
		return (-1);
	if (pipe_seq->ptype != PARSER_PIPE)
		return (execute_simple_command(pipe_seq));
	cur = pipe_seq;
	if (!cur->left)
		return (-1);
	while (cur && cur->ptype == PARSER_PIPE)
	{
		if (!cur->left || command_expansions(cur->left) < 0)
			return (-1);
		cur = cur->right;
	}
	if (!cur || command_expansions(cur) < 0)
		return (-1);
	cur = pipe_seq;
	while (cur && cur->ptype == PARSER_PIPE)
	{
		new_proc = create_proc(&new_job, cur->left);
		cur = cur->right;
	}
	new_proc = create_proc(&new_job, cur);
	launch_job(new_job);
	return (0); //TODO
}

void	print_uint(char *str, uint8_t *buf, size_t size)
{
	size_t	i = 0;

	ft_putstr(str);
	ft_putstr(" : ");
	while (i < size)
		ft_putchar(buf[i++]);
	ft_putchar('\n');
}

int		execute_and_or(t_lexer_token *and_or)
{
	t_lexer_token	*cur;
	int				execute;

	execute = 0;
	if (!and_or)
		return (-1);
	if (and_or->ptype != PARSER_AND_OR)
		return (execute_pipe(and_or));
	cur = and_or;
	while (cur && cur->ptype == PARSER_AND_OR)
	{
		if (!execute)
		{
			if (execute_pipe(cur->left) < 0)
				return (-1);
			execute = 0;
		}
		if (cur->buffer[0] == '&')
		{
			if (g_shell.exit_code != 0)
			{
				if (cur->right && cur->right->ptype != PARSER_AND_OR)
					return (0);
				execute = 1;
			}
		}
		else
		{
			if (g_shell.exit_code == 0)
			{
				if (cur->right && cur->right->ptype != PARSER_AND_OR)
					return (0);
				execute = 1;
			}
		}
		cur = cur->right;
	}
	return (execute_pipe(cur));
}

/*
** int		execute_subshell(t_lexer_token *cmd)
** {
** 	pid_t	pid;
** 	int		r;
**
** 	if ((pid = fork()) < 0)
** 		return (-1);
** 	if (pid > 0)
** 	{
** 		// TODO job control (pid)
** 		return (1); //asynchronous list
** 	}
** 	r = execute_and_or(cmd);
** 	// TODO clean
** 	exit(r < 0 ? 128 : g_shell.exit_code);
** }
**
**
** 		if (cur->buffer[0] == '&')
** 		{
** 			if (execute_subshell(cur->left) > 0)
** 				g_shell.exit_code = 0;
** 		}
** 		else if (execute_and_or(cur->left) < 0)
*/

int		execute_list(t_lexer_token *list)
{
	t_lexer_token	*cur;

	if (!list)
		return (-1);
	if (list->ptype != PARSER_SEPARATOR)
		return (execute_and_or(list));
	cur = list;
	while (cur && cur->ptype == PARSER_SEPARATOR)
	{
		if (execute_and_or(cur->left) < 0)
			return (-1);
		cur = cur->right;
	}
	if (cur)
		return (execute_and_or(cur));
	return (0);
}

int		execute_complete_command(t_lexer_token *cmd)
{
	if (!cmd)
		return (-1);
	if (execute_list(cmd) < 0)
	{
		// TODO exec error
		return (-1);
	}
	return (0);
}

int		execute(t_lexer *lex)
{
	if (!lex->root)
		return (-1);
	return (execute_complete_command(lex->root));
}
