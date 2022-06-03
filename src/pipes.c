/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdiks <cdiks@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 13:00:18 by cdiks         #+#    #+#                 */
/*   Updated: 2022/06/03 14:47:46 by rkoper        ########   odam.nl         */
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
	pid_t	id;

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

void	create_pipes(int in, int tmpout, t_parser *parser)
{
	int	end[2];
	int	out;

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

void	check_redirections(t_parser *parser)
{
	int			out;
	int			in;
	t_red		*headref;

	headref	= parser->red;
	while (parser->red)
	{
		if (parser->red->token == INFILE)
		{
			in = check_file(parser->red->file);
			dup2(in, STDIN);
		}
		if (parser->red->token == OUTFILE || parser->red->token == D_OUTFILE)
		{
			out = outfile(parser->red);
			dup2(out, STDOUT);
			close(out);
		}
		parser->red = parser->red->next;
	}
	parser->red = headref;
}

void	shell_pipex(t_data *data)
{
	int			tmpin;
	int			tmpout;
	int			in;
	char		*hid_name;

	tmpin = dup(STDIN);
	tmpout = dup(STDOUT);
	in = dup(tmpin);
	hid_name = ft_strjoin("/tmp/", check_heredoc(data->lexer));
	while (data->parser)
	{
		if (check_heredoc(data->lexer))
		{
			in = open(hid_name, O_RDONLY);
			open_heredoc(data);
		}
		create_pipes(in, tmpout, data->parser);
		check_redirections(data->parser);
		child_process(data->parser, data->env);
		data->parser = data->parser->next;
	}
	end_pipes(hid_name, tmpin, tmpout);
}
