/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 09:44:36 by rkoper            #+#    #+#             */
/*   Updated: 2022/06/03 11:22:03 by cdiks            ###   ########.fr       */
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
			free_dp(temp->command);
		free(temp);
	}
}

void	free_dp(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_redirections(t_parser **parser)
{
	t_red	*temp;
	t_red	*red;

	if (!*parser)
		return ;
	// red = *parser->red;
	while (red)
	{
		temp = red;
		red = temp->next;
		if (temp->file)
			free(temp->file);
		free(temp);
	}
}