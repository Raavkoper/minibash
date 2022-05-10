/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:54:34 by rkoper            #+#    #+#             */
/*   Updated: 2022/05/04 17:37:36 by cdiks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
		if (*line == 39 || *line == 34)
			return (1);
		line++;
	}
	return (0);
}

int	is_redirection(char c)
{
	return (c == 60 || c == 62);
}
