/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_defines.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 12:34:48 by schakor           #+#    #+#             */
/*   Updated: 2019/03/26 18:57:23 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_DEFINES_H
# define SH_DEFINES_H

# define SH_ENOMEM			1
# define SH_EINVAL			2
# define SH_ENOTTY			3
# define SH_ENOPIPE			10
# define BUFF_SIZE			1000000

# define FOUND				1
# define NOTFOUND			0

# define TRUE				1
# define FALSE				0
# define MODE_EMACS			0
# define MODE_VI_INSERT		1
# define MODE_VI_COMMAND	2
# define EDIT_MODE			3
# define KEYMAP_SIZE		47
# define SEARCHMAP_SIZE		4
# define TERM_SET			1
# define MOTION_KEYMAP_SIZE	20

# define HASHMAP_SIZE		32

#endif
