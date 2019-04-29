/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:45:05 by aguillot          #+#    #+#             */
/*   Updated: 2019/04/20 11:11:21 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	integer_expression(char *arg)
{
	if (*arg == '-' || *arg == '+')
		arg++;
	if (!*arg)
		return (0);
	while (*arg)
	{
		if (*arg < '0' || *arg > '9')
			return (0);
		arg++;
	}
	return (1);
}

int			binary_test_end(char *operand1, char *operand2, char *operator)
{
	int i1;
	int i2;

	i1 = ft_atoi(operand1);
	i2 = ft_atoi(operand2);
	if (operator[1] == 'e' && operator[2] == 'q')
		return (i1 == i2);
	if (operator[1] == 'n' && operator[2] == 'e')
		return (i1 != i2);
	if (operator[1] == 'g' && operator[2] == 't')
		return (i1 > i2);
	if (operator[1] == 'g' && operator[2] == 'e')
		return (i1 >= i2);
	if (operator[1] == 'l' && operator[2] == 't')
		return (i1 < i2);
	if (operator[1] == 'l' && operator[2] == 'e')
		return (i1 <= i2);
	return (-1);
}

int			binary_test(char *cmd, char *operand1, char *operator,
		char *operand2)
{
	int ret;

	if (operator[0] == '=' && operator[1] == '\0')
		return (ft_strcmp(operand1, operand2) == 0);
	if (operator[0] == '!' && operator[1] == '=' && operator[2] == '\0')
		return (ft_strcmp(operand1, operand2) != 0);
	if (operator[0] == '<' && operator[1] == '\0')
		return (ft_strcmp(operand1, operand2) < 0);
	if (operator[0] == '>' && operator[1] == '\0')
		return (ft_strcmp(operand1, operand2) > 0);
	if (operator[0] == '-' && operator[3] == '\0'
			&& ((operator[1] == 'e' && operator[2] == 'q')
				|| (operator[1] == 'n' && operator[2] == 'e')
				|| (operator[1] == 'g' && operator[2] == 't')
				|| (operator[1] == 'g' && operator[2] == 'e')
				|| (operator[1] == 'l' && operator[2] == 't')
				|| (operator[1] == 'l' && operator[2] == 'e')))
	{
		if (!integer_expression(operand1) || !integer_expression(operand2))
			return (unexpected(cmd, operator, "integer expression"));
		if ((ret = binary_test_end(operand1, operand2, operator)) != -1)
			return (ret);
	}
	return (unexpected(cmd, operator, "binary operator"));
}
