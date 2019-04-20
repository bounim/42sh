/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unary_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:44:53 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/20 11:14:59 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int	unary_test_end(char *operator, struct stat sb)
{
	if (operator[1] == 'b')
		return ((sb.st_mode & S_IFMT) == S_IFBLK);
	if (operator[1] == 'c')
		return ((sb.st_mode & S_IFMT) == S_IFCHR);
	if (operator[1] == 'd')
		return ((sb.st_mode & S_IFMT) == S_IFDIR);
	if (operator[1] == 'f')
		return ((sb.st_mode & S_IFMT) == S_IFREG);
	if (operator[1] == 'p')
		return ((sb.st_mode & S_IFMT) == S_IFIFO);
	if (operator[1] == 'S')
		return ((sb.st_mode & S_IFMT) == S_IFSOCK);
	if (operator[1] == 's')
		return (sb.st_size > 0);
	if (operator[1] == 'r')
		return (sb.st_mode & S_IRUSR);
	if (operator[1] == 'w')
		return (sb.st_mode & S_IWUSR);
	if (operator[1] == 'x')
		return (sb.st_mode & S_IXUSR);
	if (operator[1] == 'u')
		return (sb.st_mode & S_ISUID);
	if (operator[1] == 'g')
		return (sb.st_mode & S_ISGID);
	return (-1);
}

int	unary_test(char *cmd, char *operator, char *operand)
{
	struct stat	sb;
	int			ret;

	if (operator[1] == 'z')
		return (operand[0] == '\0');
	if (operator[1] == 'n')
		return (operand[0] != '\0');
	if (operator[1] == 'L')
		return (lstat(operand, &sb) != 0 || (sb.st_mode & S_IFMT) != S_IFLNK);
	if (stat(operand, &sb) != 0)
		return (0);
	if (operator[1] == 'e')
		return (0);
	if ((ret = unary_test_end(operator, sb)) != -1)
		return (ret);
	return (unexpected(cmd, operator, "unary operator"));
}
