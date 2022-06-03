/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 09:20:22 by cdiks             #+#    #+#             */
/*   Updated: 2022/06/03 11:44:23 by cdiks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_end(char *input, char *filename)
{
	return (ft_strncmp(input, filename, ft_strlen(filename)));
}

// char	*check_heredoc(t_parser *parser)
// {
// 	t_red	*tmp;

// 	tmp = parser->red;
// 	while (parser->red)
// 	{
// 		if (parser->red->token == D_INFILE)
// 			return (parser->red->file);
// 		parser->red = parser->red->next;
// 		printf("%d\n", parser->red->token);
// 	}
// 	parser->red = tmp;
// 	return (NULL);
// }

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
	line = readline("heredoc> ");
	while (line)
	{
		if (!check_end(line, filename))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("heredoc> ");
	}
	free(hid_name);
	free(line);
	close(fd);
}
