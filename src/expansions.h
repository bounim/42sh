/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 12:12:56 by kberisha          #+#    #+#             */
/*   Updated: 2019/04/04 12:12:58 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
#define EXPANSION_H

# include <sys/types.h>
# include <pwd.h>
# include "parser.h"


enum    state {ST_GEN, ST_BS, ST_QU, ST_DQU};

char    quoted(uint8_t *buf, size_t index);
int     tilde_expansion(t_lexer_token **root);
int		parameter_expansion(t_lexer_token *root);

#endif
