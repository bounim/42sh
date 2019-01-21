/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 16:01:13 by emartine          #+#    #+#             */
/*   Updated: 2018/10/30 16:01:16 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <limits.h>

# ifndef HOST_NAME_MAX
#  ifdef _POSIX_HOST_NAME_MAX
#   define HOST_NAME_MAX _POSIX_HOST_NAME_MAX
#  else
#   define HOST_NAME_MAX 255
#  endif
# endif

# ifndef LINE_MAX
#  define LINE_MAX 2048
# endif

/*
** canonical path:
**  is a string
**  absolute path
**  begins by a slash
**  doesn't contain members . and ..
**  is NOT terminated by a slash, except if it is /
*/

/*
** transforms a path (relative, absolute...) into a canonical path (absolute)
**
** result size is PATH_MAX + 1
** workdir is a canonical path, e.g. given by getcwd or this function
** input is a string, of any size
**
** result is a canonical path
**  if input is empty string, workdir is copied into result
**  if input doesn't start by a slash, result will start by workdir
**
** returns 0 on success, < 0 on error
**  -1 path too long to be canonicalized
*/

int		canonical_path(char *result, char *workdir, char *input);

#endif
