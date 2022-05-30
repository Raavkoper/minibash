/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:48:35 by cdiks             #+#    #+#             */
/*   Updated: 2022/05/30 13:44:46 by cdiks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_outfile(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer)
	{
		if (lexer->token == OUTFILE || lexer->token == D_OUTFILE)
			i++;
		lexer = lexer->next;
	}
	if (!i)
		return (1);
	return (0);
}

int	check_file(char filename, char *name)
{
	if (filename == 'i')
	{
		if (access(name, F_OK) == 0)
			return (open(name, O_RDONLY));
	}
	return (0);
}

char	*infile(t_lexer *lexer)
{
	char	*infile;

	while (lexer->next != NULL)
	{
		if (lexer->token == INFILE)
		{
			infile = lexer->next->command;
			return (infile);
		}
		lexer = lexer->next;
	}
	return (NULL);
}

int	outfile(t_lexer *lexer)
{
	if (lexer->token == D_OUTFILE)
	{
		if (lexer->next->command)
			return (open(lexer->next->command,
					O_CREAT | O_RDWR | O_APPEND, 0644));
	}
	else if (lexer->token == OUTFILE)
	{
		if (lexer->next->command)
			return (open(lexer->next->command,
					O_CREAT | O_RDWR | O_TRUNC, 0644));
	}
	return (0);
}
