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

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include <sys/types.h>
# include <pwd.h>
# include "parser.h"

int		command_expansions(t_lexer_token *cmd);

#endif
