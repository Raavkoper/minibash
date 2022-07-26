/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:00:18 by cdiks             #+#    #+#             */
/*   Updated: 2022/07/26 15:02:09 by cdiks            ###   ########.fr       */
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
	if (!paths[i])
	{
		if (cmdarg[0] == '/')
		{
			if (access(cmdarg, F_OK) == 0)
				return (cmdarg);
		}
	}
	while (paths[i])
	{
		if (cmdarg[0] == '/')
			final_cmd = ft_strdup(cmdarg);
		else
			final_cmd = ft_strjoin_p(ft_strjoin_p(paths[i], "/"), cmdarg);
		if (access(final_cmd, F_OK) == 0)
			return (final_cmd);
		free(final_cmd);
		i++;
	}
	return (NULL);
}

void	start_pipes(int *in, int *tmpin, int *tmpout)
{
	*tmpin = dup(STDIN);
	*tmpout = dup(STDOUT);
	*in = dup(*tmpin);
}

void	end_pipes(char *hid_name, int tmpin, int tmpout)
{
	free(hid_name);
	dup2(tmpin, STDIN);
	dup2(tmpout, STDOUT);
	close(tmpin);
	close(tmpout);
}

void	check_red(t_data **data)
{
	t_data	**tmp;

	tmp = data;
	if ((*data)->parser->has_red)
	{
		check_redirections((*data)->red);
		(*data)->red = (*data)->red->next;
	}
	data = tmp;
}

int	count_commands(t_lexer *lexer)
{
	int	i;

	i = 0;
	if (!lexer)
		return (0);
	while (lexer && lexer->token != PIPE)
	{
		if (!lexer->token)
			i += 1;
		if (is_redirection(lexer->token) || is_double(lexer->token))
		{
			if (lexer->next)
				lexer = lexer->next->next;
			else
				lexer = lexer->next;
		}
		else
			lexer = lexer->next;
	}
	return (i);
}
