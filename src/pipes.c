/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdiks <cdiks@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 13:00:18 by cdiks         #+#    #+#                 */
/*   Updated: 2022/09/15 14:26:31 by rkoper        ########   odam.nl         */
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
	if (access(*parser->command, F_OK) == 0)
		execve(*parser->command, cmdarg, env);
	final_cmd = search_path(paths, *cmdarg);
	if (final_cmd == NULL)
	{
		write(STDERR, "minishell: ", 11);
		write(STDERR, *cmdarg, ft_strlen(*cmdarg));
		write(STDERR, ": command not found\n", 20);
		g_exit_code = 127;
		exit(1);
	}
	else
		execve(final_cmd, cmdarg, env);
	return (NULL);
}

void	child_process(t_parser *parser, char **env)
{
	pid_t	id;
	int		status;

	status = 0;
	id = fork();
	if (id < 0)
	{
		perror("fork failed");
		return ;
	}
	if (id == 0)
		execute(parser, env);
	waitpid(id, &status, 0);
	if (status)
		g_exit_code = 127;
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

void	check_redirections(t_red *red)
{
	int			out;
	int			in;
	t_red		*headref;

	headref = red;
	while (red && red->token != PIPE)
	{
		if (red->token == OUTFILE || red->token == D_OUTFILE)
		{
			out = outfile(red);
			dup2(out, STDOUT);
			close(out);
		}
		else if (red->token == INFILE)
		{
			in = check_file(red->file);
			dup2(in, STDIN);
			close(in);
		}
		red = red->next;
	}
	red = headref;
}

void	shell_pipex(t_data *data)
{
	int			tmpin;
	int			tmpout;
	int			in;
	t_parser	*tmp;
	t_red		*tmp2;

	start_pipes(&in, &tmpin, &tmpout);
	tmp = data->parser;
	tmp2 = data->red;
	while (data->parser)
	{
		heredoc(data, ft_strjoin("/tmp/", check_heredoc(data->lexer)), &in);
		create_pipes(in, tmpout, data->parser);
		check_red(&data);
		if (!check_shell(data) || !find_command(data,
				*data->parser->command, data->parser->command))
			child_process(data->parser, data->env);
		data->parser = data->parser->next;
	}
	data->parser = tmp;
	data->red = tmp2;
	end_pipes(ft_strjoin("/tmp/", check_heredoc(data->lexer)), tmpin, tmpout);
}
