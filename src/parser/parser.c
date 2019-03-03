/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 18:10:56 by kberisha          #+#    #+#             */
/*   Updated: 2019/02/28 05:11:03 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

void						parser_init(t_parser *parser)
{
	ft_memset(parser, 0, sizeof(*parser));
	parser->head = NULL;
}

void						parser_create_args(t_lexer_token **head)
{
	t_lexer_token	*cur;
	t_lexer_token	*prev;

	cur = (*head)->next;
	while (cur && cur->type == LEX_TP_WD)
	{
		if (!((*head)->args[(*head)->args_nb] = malloc(cur->size * sizeof(uint8_t))))
			return ;
		ft_memcpy((*head)->args[(*head)->args_nb], cur->buffer, cur->size);
		(*head)->args_size[(*head)->args_nb] = cur->size;
		(*head)->args_nb++;
		prev = cur;
		cur = cur->next;
		lexer_free_token(&prev);
	}
	if (cur && cur->type != LEX_TP_WD)
		(*head)->next = cur;
	else
		(*head)->next = NULL;
}

/*	gets redirection type
**	logique
*/

enum	e_redirect_type		get_redirect(uint8_t *buffer, size_t size)
{
	if (size == 2)
	{
		if (!ft_memcmp(">>", (const uint8_t*)buffer, size))
			return (DGREAT);
		if (!ft_memcmp("<<", (const uint8_t*)buffer, size))
			return (DLESS);
		if (!ft_memcmp(">&", (const uint8_t*)buffer, size))
			return (GREATAND);
		if (!ft_memcmp("<&", (const uint8_t*)buffer, size))
			return (LESSAND);
		if (!ft_memcmp("<>", (const uint8_t*)buffer, size))
			return (LESSGREAT);
	}
	else if (size == 1)
	{
		if (!ft_memcmp(">", (const uint8_t*)buffer, size))
			return (GREAT);
		if (!ft_memcmp("<", (const uint8_t*)buffer, size))
			return (LESS);
	}
	return (0);
}

void							tokenstr(char *str, t_lexer_token *tok)
{
	ft_putendl(str);
	print_token(tok->buffer, tok->size);
}

/* detects redirections in token list and saves them in redirect tab of last cmd
** cmd is the last command_token and head is the redirect_token
*/

t_lexer_token					*parser_do_redirs(t_lexer_token **cmd, t_lexer_token **op, int io_nb)
{
	t_lexer_token *cur;
	t_lexer_token *prev;

	cur = (*op);
	if (!*cmd)
		return (NULL);
	(*cmd)->redirs[(*cmd)->redirs_nb].io_number = io_nb;//ft_memtoi((*io_nb)->buffer);
	(*cmd)->redirs[(*cmd)->redirs_nb].redir_type = get_redirect(cur->buffer, cur->size);
	if (cur->next && cur->next->type == LEX_TP_WD)
	{
		prev = cur;
		cur = cur->next;
		if (!((*cmd)->redirs[(*cmd)->redirs_nb].redir = malloc(cur->size * sizeof(uint8_t))))
			return (NULL);
		ft_memcpy((*cmd)->redirs[(*cmd)->redirs_nb].redir, cur->buffer, cur->size);
		(*cmd)->redirs[(*cmd)->redirs_nb].redir_size = cur->size;
		lexer_free_token(&prev);
		prev = cur;
		cur = cur->next;
		lexer_free_token(&prev);
		(*cmd)->redirs_nb++;
	}
	else
	{
		lexer_free_token(&cur);
		(*cmd)->redir_err++;
	}
	return (cur);
}

void							parser_light_redirs(t_lexer *lexer)
{
	int				io_nb;
	t_lexer_token	*cur;
	t_lexer_token	*cmd;
	t_lexer_token	*last;

	io_nb = -1;
	last = NULL;
	cur = lexer->head;
	if (cur->type == LEX_TP_WD)
		cmd = cur;
	while (cur)
	{
		tokenstr("DOING REDIRECTION", cur);
		if (cur->type == LEX_TP_OP && !get_redirect(cur->buffer, cur->size)
		&& cur->next && cur->next->type == LEX_TP_WD)
			cmd = cur->next;
		if (cur->type == LEX_TP_IO)
		{
			io_nb = atoi((char*)cur->buffer);
			last = cur;
			lexer_free_token(&last);
		}
		if (cur->next && cur->next->type == LEX_TP_OP
		&& get_redirect(cur->next->buffer, cur->next->size))
		{
			ft_putendl("IN IT");
			last = cur;
			last->next = parser_do_redirs(&cmd, &cur->next, io_nb);
		}
		if (cur->type == LEX_TP_OP && get_redirect(cur->buffer, cur->size))
		{
			if (!last)
			{
				parser_do_redirs(&lexer->nullredir, &cur, io_nb);
				last = cur;
			}
			else
				last->next = parser_do_redirs(&cmd, &cur, io_nb);
			printf("cur addr inside == %p\n", cur);
		}
		// else
		if (!cur)
			cur = last->next;
		else
			cur = cur->next;
			// break;
		printf("cur addr == %p\n", cur);

	}
}

void							parser_light_args(t_lexer *lexer)
{
	t_lexer_token	*prev;
	t_lexer_token	*cur;

	prev = NULL;
	cur = lexer->head;
	while (cur)
	{
		if (cur->type == LEX_TP_WD)
			parser_create_args(&cur);
		prev = cur;
		if (cur)
			cur = cur->next;
	}
}

int								parser_create_tree(t_lexer *lexer)
{
	t_parser		*parser;
	t_lexer_token	*tmp;
	t_parser_node	*n;

	size_t i = 0;
	n = NULL;
	if (!(parser = malloc(sizeof(*parser))))
		return (-1);
	parser_init(parser);
	lexer_print(&lexer->head);
	parser_light_redirs(lexer);
	parser_light_args(lexer);
	lexer_print(&lexer->head);
	tmp = lexer->head;
	while (tmp)
	{
		if (!(n = parser_new_elem(tmp)))
			return (-1);
		ft_putstr("currently on ");
		print_token(n->buffer, n->buffer_length);
		if (n->token->args_nb)
		{
			ft_putendl("ARGS ::");
			while (i < n->token->args_nb)
			{
				print_token(n->token->args[i], n->token->args_size[i]);
				i++;
			}
		}
		i = 0;
		if (n->token->redirs_nb)
		{
			ft_putendl("REDIRS ::");
			while (i < n->token->redirs_nb)
			{
				print_token(n->token->redirs[i].redir, n->token->redirs[i].redir_size);
				i++;
			}
		}
		parser_add_tree(&parser->head, n);
		tmp = tmp->next;
	}
	structure(parser->head, 0);
	return (0);
}
