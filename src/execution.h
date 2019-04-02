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

void	execution(t_lexer *lex);
int		command_redir(t_lexer_token *cmd);
void	command_redir_restore(t_lexer_token *cmd);

#endif
