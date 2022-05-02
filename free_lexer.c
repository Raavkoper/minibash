/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_lexer.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/02 09:44:36 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/02 10:16:35 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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