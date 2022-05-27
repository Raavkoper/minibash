/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 09:20:22 by cdiks             #+#    #+#             */
/*   Updated: 2022/05/27 14:53:59 by cdiks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_end(char *input, char *filename)
{
    return (ft_strncmp(input, filename, ft_strlen(filename)));
}

char *check_heredoc(t_lexer *lexer)
{
    char *filename;

    while (lexer)
    {
        if (lexer->token == D_INFILE)
        {
            filename = lexer->next->command;
            return (filename);
        }
        lexer = lexer->next;
    }
    return (0);
}

char    *hidden_name(char *name)
{
    char *filename;

    filename = ft_strjoin("/tmp/", name);
    return (filename);
}

void    open_heredoc(t_lexer *lexer)
{
    char *line;
    char *filename;
    char *hid_name;
    int  fd;

    line = readline("heredoc> ");
    hid_name = hidden_name(check_heredoc(lexer));
    filename = check_heredoc(lexer);
    fd = open(hid_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
    while (line)
    {
        if (!check_end(line, filename))
           break ;
        free(line);
        line = readline("heredoc> ");
    }
    free(line);
    close(fd);
    return ;
}
