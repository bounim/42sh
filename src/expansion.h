#ifndef EXPANSION_H
#define EXPANSION_H

# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include "parser.h"
# include "lexer.h"


void	do_expansions(char **env, t_parser_node *tree);
/*
** Tilde expansion
*/
int     tilde_expansion(char **env, t_parser_node **head);
/*
** Parameter expansion
*/

/*
** Command substitution
*/

/*
** Arithmetic expansion
*/

/*
** Field splitting
*/

/*
** Pathname expansion
*/

/*
** Quote removal
*/


#endif
