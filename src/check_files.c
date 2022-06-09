/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:48:35 by cdiks             #+#    #+#             */
/*   Updated: 2022/06/08 15:31:08 by cdiks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_outfile(t_lexer *lexer)
{
	int		i;
	t_lexer	*tmp;

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

int	check_file(char *name)
{
	if (access(name, F_OK) == 0)
		return (open(name, O_RDONLY));
	return (0);
}

int	outfile(t_red *red)
{
	if (red->token == D_OUTFILE)
	{
		if (red->file)
			return (open(red->file,
					O_CREAT | O_RDWR | O_APPEND, 0644));
	}
	else if (red->token == OUTFILE)
	{
		if (red->file)
			return (open(red->file,
					O_CREAT | O_RDWR | O_TRUNC, 0644));
	}
	return (0);
}
