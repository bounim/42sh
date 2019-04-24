/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 15:52:44 by emartine          #+#    #+#             */
/*   Updated: 2019/03/21 15:52:47 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "parser.h"

int		execute(t_lexer *lex);
char	*command_search(t_lexer_token *cmd, t_envl *envl);
char	*find_command(char *cmd, t_envl *envl);
int		exec_error(char *cmd, char *path);
int		command_redir(t_lexer_token *cmd);
void	command_redir_restore(t_lexer_token *cmd);
int		execute_assign_list(t_lexer_token *cmd, t_proc *proc);
char	*lst_to_str(t_lexer_token *head);
char	**arg_to_argv(t_lexer_token *cmd);

int		redir_op(t_lexer_token *cmd, t_lexer_token *cur);
int		error_restore(t_lexer_token *cmd, char *msg);

#endif
