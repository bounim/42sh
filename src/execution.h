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

# include <limits.h>
# include "parser.h"

int		execute(t_lexer *lex);

/*
** find_command returns:
** > 0 if found but can't be executed (for paths with slashes, not commands)
**   1 if cannot stat
**   2 if is a directory
**   3 if no execute permission
** < 0 if not found
** = 0 if found and can be executed
*/

int		find_command(char path[PATH_MAX + 1], char *cmd, t_envl *envl);
void	exec_error(char *cmd, int r);
int		command_redir(t_lexer_token *cmd);
void	command_redir_restore(t_lexer_token *cmd);
int		execute_assign_list(t_lexer_token *cmd, t_proc *proc);
char	*lst_to_str(t_lexer_token *head);
char	**arg_to_argv(t_lexer_token *cmd);
void	write_error(char *cmd, char *str);

int		redir_op(t_lexer_token *cmd, t_lexer_token *cur);
int		error_restore(t_lexer_token *cmd, char *msg);
int		read_heredoc(t_lexer *lex, size_t *i);
int		will_close(t_lexer_token *cmd, int fd);
void	lazy_close(t_lexer_token *cmd);
int		test_fd_new_closed(t_lexer_token *cmd, t_lexer_token *cur);
void	close_fd_before_exec(t_lexer_token *cmd);

#endif
