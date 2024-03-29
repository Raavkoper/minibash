/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdiks <cdiks@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 13:00:18 by cdiks         #+#    #+#                 */
/*   Updated: 2022/09/15 12:13:11 by rkoper        ########   odam.nl         */
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
		while ((*data)->red && (*data)->red->token != PIPE)
			(*data)->red = (*data)->red->next;
		if ((*data)->red)
			(*data)->red = (*data)->red->next;
	}
	data = tmp;
}
