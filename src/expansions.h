#ifndef EXPANSION_H
#define EXPANSION_H

# include <sys/types.h>
# include <pwd.h>
# include "parser.h"

enum    state {ST_GEN, ST_BS, ST_QU, ST_DQU};

char    quoted(uint8_t *buf, size_t index);
/*
** Tilde expansion
*/
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
