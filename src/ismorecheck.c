/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ismorecheck.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/06 15:09:59 by rkoper        #+#    #+#                 */
/*   Updated: 2022/06/14 14:28:11 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(char c)
{
	if (c == INFILE)
		return (INFILE);
	if (c == OUTFILE)
		return (OUTFILE);
	return (0);
}

int	is_is(char *line)
{
	while (*line && !iswhitespace(*line))
	{
		if (*line == 61)
			return (1);
		line++;
	}
	return (0);
}

int	is_wholenum(char *line)
{
	while (*line && ft_isdigit(*line))
		line++;
	if (*line)
		return (0);
	return (1);
}

int	isdollar(char *line)
{
	while (*line)
	{
		if (*line == 36)
			return (1);
		line++;
	}
	return (0);
}
