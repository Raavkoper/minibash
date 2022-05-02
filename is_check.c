/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:54:34 by rkoper            #+#    #+#             */
/*   Updated: 2022/05/02 10:11:46 by cdiks            ###   ########.fr       */
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

int check_quotes(char *line)
{
	int	i;
	int	s_quotes;
	int	d_quotes;

	s_quotes = 0;
	d_quotes = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == 34)
		{
			d_quotes++;
			i++;
		}
		else if (line[i] == 39)
		{
			s_quotes++;
			i++;
		}
		i++;
	}
	if ((s_quotes % 2) != 0 || (d_quotes % 2 != 0))
		printf("No closing quote\n");
	return (0);
}
