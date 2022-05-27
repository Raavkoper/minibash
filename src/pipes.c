/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:00:18 by cdiks             #+#    #+#             */
/*   Updated: 2022/05/27 14:16:56 by cdiks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*execute(t_parser *parser, char **env)
{
	char	**paths;
	char	**cmdarg;
	char	*path_env;
	char	*final_cmd;

	path_env = get_path(env);
	paths = ft_split(path_env, ':');
	cmdarg = parser->command;
	final_cmd = search_path(paths, *cmdarg);
	if (final_cmd == NULL)
		exit(1);
	else
		execve(final_cmd, cmdarg, env);
	perror("could not execute");
	return (0);
}

void	child_process(t_parser *parser, char **env)
{
    pid_t   id;
    
    id = fork();
    if (id < 0)
	{
		perror("fork failed");
		return ;
	}
    else if (id == 0)
	    execute(parser, env);
    else
        waitpid(id, NULL, 0);
}

void    create_pipes(int in, int tmpout, t_parser *parser)
{
    int end[2];
    int out;

    out = dup(tmpout);
    dup2(in, STDIN);
    close(in);
    if (parser->next != NULL)
    {
        pipe(end);
        out = end[1];
	    in = end[0];
    }
	dup2(out, STDOUT);
   	close(out);
}

void	check_redirections(t_data *data, int in, t_parser *temp)
{
	int out;

	while (data->lexer)
	{
		if (data->lexer->token == INFILE)
		{
			in = check_file('i', infile(data->lexer));
			dup2(in, STDIN);
			data->lexer = data->lexer->next;
		}
		if (data->lexer->token == OUTFILE || data->lexer->token == D_OUTFILE)
		{
			out = outfile(data->lexer);
			dup2(out, STDOUT);
			close(out);
			data->lexer = data->lexer->next;
		}
		data->lexer = data->lexer->next;
	}
}

void    shell_pipex(t_data *data)
{
    int 		tmpin;
	int 		tmpout;
	int 		in;
	t_parser	*temp;

    temp = data->parser;
    tmpin = dup(STDIN);
	tmpout = dup(STDOUT);
	in = dup(tmpin);
    while (temp)
    {
		if (check_heredoc(data->lexer))
		{
			in = open(hidden_name(check_heredoc(data->lexer)), O_RDONLY);
			open_heredoc(data->lexer);
		}
        create_pipes(in, tmpout, temp);
		check_redirections(data, in, temp);
        child_process(temp, data->env);
        temp = temp->next;
    }
    dup2(tmpin, STDIN);
	dup2(tmpout, STDOUT);
	close(tmpin);
	close(tmpout);
}