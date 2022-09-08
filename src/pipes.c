/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:00:18 by cdiks             #+#    #+#             */
/*   Updated: 2022/09/08 12:03:06 by cdiks            ###   ########.fr       */
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
		printf("minishell: %s: command not found\n", *cmdarg);
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
		g_exit_code = WEXITSTATUS(status);
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
	while (red)
	{
		if (red->token == OUTFILE || red->token == D_OUTFILE)
		{
			out = outfile(red);
			dup2(out, STDOUT);
			close(out);
			red = red->next;
		}
		else if (red->token == INFILE)
		{
			in = check_file(red->file);
			dup2(in, STDIN);
			close(in);
			red = red->next;
		}
		else
			red = red->next;
	}
	red = headref;
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
		heredoc(data, hid_name, &in);
		create_pipes(in, tmpout, data->parser);
		check_red(&data);
		if (!check_shell(data) || !find_command(data,
				*data->parser->command, data->parser->command))
			child_process(data->parser, data->env);
		data->parser = data->parser->next;
	}
	data->parser = tmp;
	end_pipes(hid_name, tmpin, tmpout);
}
