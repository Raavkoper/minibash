/* ************************************************************************** */
/*                                                                            */
<<<<<<< HEAD
/*                                                        ::::::::            */
/*   is_check.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdiks <cdiks@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 14:54:34 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/23 09:12:18 by rkoper        ########   odam.nl         */
=======
/*                                                        :::      ::::::::   */
/*   is_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:54:34 by rkoper            #+#    #+#             */
/*   Updated: 2022/05/23 09:03:07 by cdiks            ###   ########.fr       */
>>>>>>> 814ca4ad7d14bee6ca9763ddbeed20a37b733554
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	iswhitespace(char c)
{
	return (c == 32 || c == 10 || c == 9 || c == 11);
}

int istoken(char c)
{
	return (c == 60 || c == 62 || c == 39 || c == 34 || c == 124);
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

int	is_redirection(char c)
{
	return (c == 60 || c == 62);
}

int	isis(char *line)
{
	while (*line && !iswhitespace(*line))
	{
		if (*line == 61)
			return (1);
		line++;
	}
	return (0);
}

int	isdollar(char *line)
{
	while (*line && !iswhitespace(*line))
	{
		if (*line == 36)
			return (1);
		line++;
	}
	return (0);
}
