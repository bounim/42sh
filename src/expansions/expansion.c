/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:21:23 by kberisha          #+#    #+#             */
/*   Updated: 2019/04/03 16:21:25 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"


void	do_expansions(t_lexer_token *root)
{
	if (!root)
		return ;
	else
	{
		do_expansions(root->right);
		if (root->type == PARSER_COMMAND)
		{
			tilde_expansion(&root);
			parameter_expansion(&root);
		}
		do_expansions(root->left);
	}
}
