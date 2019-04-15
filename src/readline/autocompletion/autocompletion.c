/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:00:11 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/15 14:00:13 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int		find_context(t_char_list *char_list, t_char *point_char)
{
	
}

void	autocompletion(void)
{
	int context;

	context = find_context(g_shell.edit.char_list, g_shell.edit.point_char);
	//1. recherche position pour savoir quoi retourner
	//2. build list pour affichage
	//3. 
}