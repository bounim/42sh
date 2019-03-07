/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:24:31 by kberisha          #+#    #+#             */
/*   Updated: 2019/02/27 15:24:33 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

uint8_t		is_shift(uint8_t *buffer, size_t buffer_size)
{
	if (buffer_size > 2 || (buffer[0] != '<' && buffer[0] != '>'))
		return (0);
	if (buffer_size == 1)
    return (1);
  if (buffer[1] && buffer[1] == '&')
    return (1);
  else
    return (buffer[0] == buffer[1]);
}

uint8_t		is_semicolon(uint8_t *buffer, size_t buffer_size)
{
    if (buffer_size == 1 && buffer[0] == ';')
        return (1);
    return (0);
}

uint8_t		is_pipeline(uint8_t *buffer, size_t buffer_size)
{
    if (buffer_size == 1 && buffer[0] == '|')
        return (1);
    return (0);
}

uint8_t		is_and(uint8_t *buffer, size_t buffer_size)
{
    if (buffer_size > 2 || buffer[0] != '&')
        return (0);
    if (buffer_size == 1)
		return (1);
	return (buffer[0] == buffer[1]);
}

uint8_t		is_or(uint8_t *buffer, size_t buffer_size)
{
    if (buffer_size == 2 && buffer[0] == '|' && buffer[1] == '|')
        return (1);
    return (0);
}