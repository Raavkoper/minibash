/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:00:18 by cdiks             #+#    #+#             */
/*   Updated: 2022/05/16 11:38:07 by cdiks            ###   ########.fr       */
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
	execute(parser, env);
}

int	check_file(char filename, char *name)
{
	if (filename == 'i')
	{
		if (access(name, F_OK) == 0)
			return (open(name, O_RDONLY));
		else
			return (0);
	}
	else
		return (open(name, O_CREAT | O_RDWR | O_TRUNC, 0644));
	return (0);
}

char	*infile(t_lexer *lexer)
{
	char *infile;

	while (lexer->next != NULL)
	{
		if (lexer->token == INFILE)
		{
			infile = lexer->next->command;
			return (infile);
		}
		lexer = lexer->next;
	}
	return (NULL);
}

char	*outfile(t_lexer *lexer)
{
	char *outfile;

	while (lexer->next != NULL)
	{
		if (lexer->token == OUTFILE)
		{
			outfile = lexer->next->command;
			return (outfile);
		}
		lexer = lexer->next;
	}
	return (NULL);
}

void	shell_pipex(t_data *data)
{
	int 		tmpin;
	int 		tmpout;
	int 		out;
	int 		in;
	pid_t 		id;
	int 		end[2];
	t_parser	*temp;

	temp = data->parser;
	tmpin = dup(STDIN);
	tmpout = dup(STDOUT);
	if (check_file('i', infile(data->lexer)))
		in = open(infile(data->lexer), O_RDONLY);
	else
		in = dup(tmpin);
	while (temp)
	{
		dup2(in, STDIN);
		if (temp->next == NULL)
		{
			if (check_file('o', outfile(data->lexer)))
				out = open(outfile(data->lexer), O_CREAT | O_RDWR | O_TRUNC, 0644);
			else
				out = dup(tmpout);
		}
		else
		{
			pipe(end);
			out = end[1];
			in = end[0];
		}
		id = fork();
		if (id == 0)
		{
			dup2(out, STDOUT);
			child_process(temp, data->env);
			close(in);
		}
		else if (id < 0) 
		{
			perror("fork failed");
			return ;
		}
		dup2(in, STDIN);
		waitpid(id, NULL, 0);
		close(out);
		temp = temp->next;
	}
	dup2(tmpin, STDIN);
	dup2(tmpout, STDOUT);
	close(tmpin);
	close(tmpout);
}
