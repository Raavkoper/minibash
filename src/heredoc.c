/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 09:20:22 by cdiks             #+#    #+#             */
/*   Updated: 2022/05/30 13:28:45 by cdiks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_end(char *input, char *filename)
{
    return (ft_strncmp(input, filename, ft_strlen(filename)));
}

char *check_heredoc(t_lexer *lexer)
{
    while (lexer)
    {
        if (lexer->token == D_INFILE)
            return (lexer->next->command);
        lexer = lexer->next;
    }
    return (NULL);
}

void    open_heredoc(t_lexer *lexer)
{
    char *line;
    char *filename;
    char *hid_name;
    int  fd;

    hid_name = ft_strjoin("/tmp/", check_heredoc(lexer));
    filename = check_heredoc(lexer);
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
    close(fd);
    free(line);
}
