/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:00:18 by cdiks             #+#    #+#             */
/*   Updated: 2022/05/12 10:33:42 by cdiks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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

char	*execute(char *cmd, char **env)
{
	char	**paths;
	char	**cmdarg;
	char	*path_env;
	char	*final_cmd;

	path_env = get_path(env);
	paths = ft_split(path_env, ':');
	cmdarg = ft_split(cmd, ' ');
	final_cmd = search_path(paths, cmdarg[0]);	
	if (final_cmd == NULL)
		exit(0);
	else
		execve(final_cmd, cmdarg, env);
	perror("could not execute");
	return (0);
}

void	child_process(char *cmd1, char **env)
{
	execute(cmd1, env);
}

void	parent_process(int *end, char *cmd2, char **env)
{
	int		x;

	waitpid(-1, NULL, 0);
	x = dup2(end[0], STDIN);
	if (x < 0)
		return (perror("dup failed"));
	close(end[1]);
	execute(cmd2, env);
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
	// int tmpin;
	// int tmpout;
	// int in;
	// int out;
	// int id;
	// int end[2];

	// // set input, check if file exists or not
	// tmpin = dup(STDIN);
	// tmpout = dup(STDOUT);
	// if (check_file('i', infile(data->lexer)))
	// 	in = open(infile(data->lexer), O_RDONLY);
	// else
	// 	in = dup(tmpin);
	// if (!in || !out)
	// 	perror("dup failed");
	// // loop through command table and create process for every command
	// while (data->parser)
	// {
	// 	dup2(in, STDIN);
	// 	close(in);
	// 	// if last command in command table
	// 	if (!data->parser->next)
	// 	{
	// 		if (check_file('o', outfile(data->lexer)))
	// 			out = open(outfile(data->lexer), O_CREAT | O_RDWR | O_TRUNC, 0644);
	// 		else
	// 			out = dup(tmpout);
	// 	}
	// 	else
	// 	{
	// 		pipe(end);
	// 		out = end[1];
	// 		in = end[0];
	// 	}
	// 	dup2(out, STDOUT);
	// 	printf("Hi\n");
	// 	close(out);
		
	// 	// create child process
	// 	id = fork();
	// 	if (id == 0) // means there is a child process
	// 	{
	// 		execute(*data->parser->command, data->env);
	// 		perror("execute child");
	// 		return ;
	// 	}
	// 	else if (id < 0) // fork failed
	// 	{
	// 		perror("fork failed");
	// 		return ;
	// 	}
	// 	data->parser = data->parser->next;
	// }
	// waitpid(id, NULL, 0);
	// dup2(in, STDIN);
	// dup2(out, STDOUT);
	// close(in);
	// close(out);

	int id;
	while (data->parser) 
	{
		id = fork(); 
		if (id == 0) 
			child_process(*data->parser->command, data->env);
		else if (id < 0) 
		{
			perror("fork");
			return; 
		}
		waitpid(id, NULL, 0);
		data->parser = data->parser->next;
	}
}
