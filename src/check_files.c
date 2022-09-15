/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_files.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdiks <cdiks@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/20 13:48:35 by cdiks         #+#    #+#                 */
/*   Updated: 2022/09/15 14:34:08 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_outfile(t_lexer *lexer)
{
	int		i;

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

void	red_token_check(t_data *data)
{
	if (is_redirection(data->lexer->token) || is_double(data->lexer->token))
	{
		data->red->token = data->lexer->token;
		if (data->lexer->next && data->lexer->next->command)
			data->red->file = ft_strdup(data->lexer->next->command);
		data->red = data->red->next;
	}
}

int	check_shell(t_data *data)
{
	if (!data->lexer)
		return (0);
	if (check_heredoc(data->lexer))
		return (0);
	if (data->parser->has_red)
		return (0);
	return (1);
}
