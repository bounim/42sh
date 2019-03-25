#ifndef EXPANSION_H
#define EXPANSION_H

# include <sys/types.h>
# include <pwd.h>
# include "parser.h"


void	do_expansions(t_lexer *lex);
/*
** Tilde expansion
*/
int     tilde_expansion(t_lexer_token *command);
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
