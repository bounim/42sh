/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_internal.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:56:13 by emartine          #+#    #+#             */
/*   Updated: 2019/04/09 17:56:48 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_INTERNAL_H
# define EXPANSIONS_INTERNAL_H

# include "twenty_one_sh.h"
# include "expansions.h"

int		arg_expansions(t_lexer_token *cmd);
int		redir_expansions(t_lexer_token *cmd);
int		assign_expansions(t_lexer_token *cmd);

int		isvarchar(uint8_t ch);
int		iswordchar(uint8_t ch);

int		buffer_expand(t_lexer_token *tok);

int		buffer_append(t_lexer_token *tok, uint8_t *buffer, size_t size);
size_t	tilde_expand(t_lexer_token *tok, size_t j, size_t k);
void	var_expand(t_lexer_token *tok, size_t j, size_t k);

#endif
