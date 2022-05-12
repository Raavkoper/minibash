/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/02 09:44:36 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/12 12:03:24 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(t_lexer **lexer)
{
	t_lexer	*temp;

	if (!*lexer)
		return ;
	while (*lexer)
	{
		temp = *lexer;
		*lexer = temp->next;
		if (temp->command)
			free(temp->command);
		free(temp);
	}
}

void	free_parser(t_parser **parser)
{
	t_parser *temp;

	if (!*parser)
		return ;
	while (*parser)
	{
		temp = *parser;
		*parser = temp->next;
		if (temp->command)
		{
			free_command_stack(temp->command);
			free(temp->command);
		}
		free(temp);
	}
}

void	free_command_stack(char **command)
{
	while (*command)
	{
		free(*command);
		command++;
	}
}

void	free_redirections(t_red **red)
{
	t_red	*temp;

	if (!*red)
		return ;
	while (*red)
	{
		temp = *red;
		*red = temp->next;
		if (temp->file)
			free(temp->file);
		free(temp);
	}
}