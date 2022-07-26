/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_check.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdiks <cdiks@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 14:54:34 by rkoper        #+#    #+#                 */
/*   Updated: 2022/06/09 14:17:50 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	iswhitespace(char c)
{
	return (c == 32 || c == 10 || c == 9 || c == 11);
}

int	istoken(char c)
{
	return (c == 60 || c == 62 || c == 39 || c == 34 || c == 124);
}

int	is_double(int c)
{
	return (c == 310 || c == 312);
}

int	isquote(char *line)
{
	while (*line && !iswhitespace(*line))
	{
		if (*line == 39)
			return (39);
		if (*line == 34)
			return (34);
		line++;
	}
	return (0);
}
