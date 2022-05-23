/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:48:35 by cdiks             #+#    #+#             */
/*   Updated: 2022/05/20 13:50:47 by cdiks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int has_outfile(t_lexer *lexer)
{
	int i;
	
	i = 0;
	while (lexer)
	{
		if (lexer->token == OUTFILE)
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
		else
			return (0);
	}
	else
		return (open(name, O_CREAT | O_RDWR | O_TRUNC, 0644));
	return (0);
}

char	*infile(t_lexer *lexer)
{
	char *infile;

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

char	*outfile(t_lexer *lexer)
{
	char 	*outfile;

	if (has_outfile(lexer))
		return (NULL);
	while (lexer->next != NULL)
	{
		if (lexer->token == OUTFILE)
		{
			outfile = lexer->next->command;
			open(lexer->next->command, O_CREAT | O_RDWR | O_TRUNC, 0644);
		}
		lexer = lexer->next;
	}
	return (outfile);
}