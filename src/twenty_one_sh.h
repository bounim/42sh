/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twenty_one_sh.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 13:06:41 by schakor           #+#    #+#             */
/*   Updated: 2019/02/06 14:25:09 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TWENTY_ONE_SH_H
# define TWENTY_ONE_SH_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include "libft.h"
# include <signal.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>
# include <stdint.h>
# include <pwd.h>

# include "sh_typedefs.h"
# include "sh_defines.h"
# include "shell.h"
# include "env.h"
# include "readline.h"
# include "history.h"
# include "lexer.h"

void						ft_sig_handler(int signo);
void						ft_signal(int signo);

// FIXME tmp func

# define BUFF_SIZE 100000

void						ft_putendl_fd(char const *s, int fd);
void						ft_putstr(char const *s);
void						ft_putchar(char ch);
void						ft_putnbr(int nb);

#endif
