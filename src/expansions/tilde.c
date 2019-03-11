/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:11:47 by kberisha          #+#    #+#             */
/*   Updated: 2019/03/11 16:11:48 by kberisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

size_t  tilde_prefix_len(uint8_t *buf, size_t size, size_t start, uint8_t assign)
{
    size_t  len;

    len = start;
    if (buf[start] == '~')
    {
        while (len < size && buf[len] != '/' && (assign == 1 && buf[len] != ':')
            && !is_quote(buf[len])) //rajouter state quoted
        {
            len++;
        }
        printf("len = %zu\n", len);
        if (len == 1)
            // replace tilde prefix by HOME value, if set
        else if
            // 
        else
            // 
    }
}

int     do_tilde_arg(t_word *arg_head)
{
    t_word  *tmp;
    
     tmp = arg_head;
     while (tmp)
     {
        if (tmp->size >= 1 && tmp->buf[0] == '~')
        {
            tilde_prefix_len(tmp->buf, tmp->size, 0, 0);
            tmp->tilded = 1;
        }
        tmp = tmp->next;
     }
}

int     tilde_expansion(t_parser_node **head)
{
    do_tilde_arg((*head)->arg_head);
    // do_tilde_assign((*head)->assign_head);
    // do_tilde_redir((*head)->redir_head);
}

void	expansions(t_parser_node **tree)
{
	if (!*tree)
		return ;
	if ((*tree)->right)
	{
		ft_putendl("printing left");
		expansions((*tree)->right);
	}
	// print_token((*tree)->arg_head->buf, (*tree)->arg_head->size);
    tilde_expansion(tree);
	if ((*tree)->left)
	{
		ft_putendl("printing left");
		expansions((*tree)->left);
	}
}