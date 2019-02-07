/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_defines.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:39:00 by schakor           #+#    #+#             */
/*   Updated: 2019/02/04 16:57:14 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RL_DEFINES_H
# define RL_DEFINES_H

# define PERFECT_KEY_MATCH		0
# define PARTIAL_KEY_MATCH		1
# define NO_KEY_MATCH			2

# define KEYSTR_CTRL_B			"\002"
# define KEYSTR_CTRL_F			"\006"
# define KEYSTR_ESC_B			"\033b"
# define KEYSTR_ESC_F			"\033f"
# define KEYSTR_CTRL_A			"\001"
# define KEYSTR_CTRL_E			"\005"
# define KEYSTR_CTRL_X_X		"\030\030"
# define KEYSTR_BACKSPACE		"\177"
# define KEYSTR_DEL				"\033[3~"
# define KEYSTR_CTRL_D			"\004"
# define KEYSTR_CTRL_U			"\025"
# define KEYSTR_CTRL_K			"\013"
# define KEYSTR_ESC_D			"\033d"
# define KEYSTR_CTRL_W			"\027"
# define KEYSTR_LEFT_ARROW		"\033[D"
# define KEYSTR_RIGHT_ARROW		"\033[C"
# define KEYSTR_UP_ARROW		"\033[A"
# define KEYSTR_DOWN_ARROW		"\033[B"
# define KEYSTR_HOME			"\033[H"
# define KEYSTR_END				"\033[F"
# define KEYSTR_RETURN			"\012"

# define MODES					3
# define MODE_EMACS				0
# define MODE_VI_INSERT			1
# define MODE_VI_COMMAND		2
# define KEYMAP_SIZE			21

#endif
