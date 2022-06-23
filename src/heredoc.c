/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 09:20:22 by cdiks             #+#    #+#             */
/*   Updated: 2022/06/23 14:49:29 by cdiks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_end(char *input, char *filename)
{
	return (ft_strncmp(input, filename, ft_strlen(filename)));
}

char	*check_heredoc(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	while (lexer)
	{
		if (lexer->token == D_INFILE)
			return (lexer->next->command);
		lexer = lexer->next;
	}
	lexer = tmp;
	return (NULL);
}

void	open_heredoc(t_data *data)
{
	char	*line;
	char	*filename;
	char	*hid_name;
	int		fd;

	hid_name = ft_strjoin("/tmp/", check_heredoc(data->lexer));
	filename = check_heredoc(data->lexer);
	fd = open(hid_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline("> ");
	if (line)
		line = expander(data->env, line, data);
	while (line)
	{
		if (!check_end(line, filename))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
		line = expander(data->env, line, data);
	}
	free(hid_name);
	free(line);
	close(fd);
}

void	heredoc(t_data *data, char *hid_name, int *in)
{
	if (check_heredoc(data->lexer))
	{
		*in = open(hid_name, O_RDONLY);
		open_heredoc(data);
	}
}
