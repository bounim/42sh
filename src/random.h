/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:00:24 by emartine          #+#    #+#             */
/*   Updated: 2019/04/11 17:00:26 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_H
# define RANDOM_H

# include <limits.h>

/*
** Create a random file, save its path to path and return its fd.
** Returns < 0 on error.
** Don't forget to close the fd and unlink the path when done!
*/

int		random_file(char path[PATH_MAX + 1]);

#endif
