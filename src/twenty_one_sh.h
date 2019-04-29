/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twenty_one_sh.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 13:06:41 by schakor           #+#    #+#             */
/*   Updated: 2019/03/07 17:37:41 by schakor          ###   ########.fr       */
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
# include "env.h"
# include "history.h"
# include "line_editing.h"
# include "lexer.h"
# include "builtin.h"
# include "job_control.h"
# include "shell.h"
# include "random.h"

void						ft_putendl_fd(char const *s, int fd);
void						ft_putstr(char const *s);
void						ft_putchar(char ch);
void						ft_putnbr(int nb);
void						ft_putendl(char *str);

#endif
