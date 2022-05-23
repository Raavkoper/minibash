/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:00:18 by cdiks             #+#    #+#             */
/*   Updated: 2022/05/23 12:53:02 by cdiks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}


char	*search_path(char **paths, char *cmdarg)
{
	int		i;
	char	*final_cmd;

	i = 0;
	while (paths[i])
	{
		final_cmd = ft_strjoin_p(ft_strjoin_p(paths[i], "/"), cmdarg);
		if (access(final_cmd, F_OK) == 0)
			return (final_cmd);
		free(final_cmd);
		i++;
	}
	return (NULL);
}

char *double_reds(t_lexer *lexer)
{
	char	*out;

	while (lexer->next != NULL)
	{
		if (lexer->token == OUTFILE && lexer->next->token == OUTFILE)
			return (lexer->next->next->command);
		lexer = lexer->next;
	}
	return (NULL);
}

int	check_doubles(t_lexer *lexer)
{
	while (lexer)
	{
		if (lexer->token == OUTFILE && lexer->next->token == OUTFILE)
			return (1);
		lexer = lexer->next;
	}
	return (0);
}
