/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdiks <cdiks@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 13:00:18 by cdiks         #+#    #+#                 */
/*   Updated: 2022/06/09 13:58:57 by rkoper        ########   odam.nl         */
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
	int 	status;

	id = fork();
	status = 0;
	if (id < 0)
	{
		perror("fork failed");
		return ;
	}
	else if (id == 0)
		execute(parser, env);
	else
		waitpid(id, &status, 0);
	if (status)
		g_exit_code = status;
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

void	check_redirections(t_data *data)
{
	int			out;
	int			in;
	t_red		*headref;

	headref = data->red;
	while (data->red)
	{
		if (data->red->token == INFILE)
		{
			in = check_file(data->red->file);
			dup2(in, STDIN);
			close(in);
		}
		if (data->red->token == OUTFILE || data->red->token == D_OUTFILE)
		{
			out = outfile(data->red);
			dup2(out, STDOUT);
			close(out);
		}
		data->red = data->red->next;
	}
	data->red = headref;
}

void	shell_pipex(t_data *data)
{
	int			tmpin;
	int			tmpout;
	int			in;
	char		*hid_name;
	t_parser	*tmp;

	start_pipes(&in, &tmpin, &tmpout);
	hid_name = ft_strjoin("/tmp/", check_heredoc(data->lexer));
	tmp = data->parser;
	while (data->parser)
	{
		if (!check_shell(data) || !find_command(data, *data->parser->command, data->parser->command))
		{
			if (check_heredoc(data->lexer))
			{
				in = open(hid_name, O_RDONLY);
				open_heredoc(data);
			}
			create_pipes(in, tmpout, data->parser);
			if (data->parser->has_red)
				check_redirections(data);
			child_process(data->parser, data->env);
		}
		data->parser = data->parser->next;
	}
	data->parser = tmp;
	end_pipes(hid_name, tmpin, tmpout);
}

int	check_shell(t_data *data)
{
	if (!data->lexer)
		return (0);
	if (check_heredoc(data->lexer))
		return (0);
	if (data->parser->has_red)
		return (0);
	return (1);
}
