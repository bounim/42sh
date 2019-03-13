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
        while (len < size && buf[len] != '/' && (buf[len] != ':' || assign == 0)
            && !is_quote(buf[len])) //rajouter state quoted
        {
            len++;
        }
        printf("len = %zu\n", len);
    }
    return (len);
}

char	*get_env(char **env, char *elem)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	j = ft_strlen(elem);
	tmp = NULL;
	while (env[i])
	{
		if (!ft_memcmp(env[i], elem, j) && env[i][j] == '=')
		{
			tmp = env[i] + j + 1;
			break ;
		}
		i++;
	}
	return (*tmp != '\0' ? tmp : NULL);
}

char     *tilde_result(char **env, t_word *tmp, size_t len)
{
  char *result; //ou uint8_t ??

  result = NULL;
  if (len == 1)
  {
    result = get_env(env, "HOME");
    ft_memset(tmp->buf, 0, tmp->size);
    ft_memcpy(result, tmp->buf, ft_strlen(result));
    printf("DONE TILDE\n");
  }
  // replace tilde prefix by HOME value, if set
  // else if
  //
  // else
  //
  return (result);
}

int     do_tilde_arg(char **env, t_word *arg_head)
{
    t_word  *tmp;
    size_t  len;

     tmp = arg_head;
     while (tmp)
     {
        if (tmp->size >= 1 && tmp->buf[0] == '~')
        {
            len = tilde_prefix_len(tmp->buf, tmp->size, 0, 0);
            tilde_result(env, tmp, len);
            tmp->tilded = 1;
        }
        tmp = tmp->next;
     }
     return (0);
}

int     tilde_expansion(char **env, t_parser_node **head)
{
  ft_putendl("DOING EXPANSIONS");
    do_tilde_arg(env, (*head)->arg_head);
    // do_tilde_assign((*head)->assign_head);
    // do_tilde_redir((*head)->redir_head);
    return (0);
}

void	do_expansions(char **env, t_parser_node **tree)
{
	if (!*tree)
		return ;
	if ((*tree)->right)
	{
		ft_putendl("printing left");
		do_expansions(env, &(*tree)->right);
	}
	// print_token((*tree)->arg_head->buf, (*tree)->arg_head->size);
    tilde_expansion(env, tree);
	if ((*tree)->left)
	{
		ft_putendl("printing left");
		do_expansions(env, &(*tree)->left);
	}
}
