/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_typedefs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 11:27:19 by schakor           #+#    #+#             */
/*   Updated: 2018/12/17 14:15:09 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_TYPEDEFS_H
# define SH_TYPEDEFS_H

/*
**	typedefs header for the 42sh
*/

typedef unsigned char			t_uint8;
typedef unsigned short			t_uint16;
typedef unsigned int			t_uint32;
typedef unsigned long long		t_uint64;
typedef char					t_int8;
typedef short					t_int16;
typedef int						t_int32;
typedef long long				t_int64;
typedef unsigned char			t_bool;

typedef struct termios			t_termios;
typedef struct s_shell			t_shell;
typedef struct s_envl			t_envl;
typedef struct s_input			t_input;
typedef struct s_history		t_history;

#endif
