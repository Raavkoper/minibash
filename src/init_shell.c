#include "minishell.h"

char *init_shell(void)
{
	char *line;

	line = (char *)readline("\033[1m\033[32mminishell$>\x1B[0m ");
	add_history(line);
	return (line);
}

void	run_shell(t_data *data)
{
	char *line;

	while (1)
	{
		line = init_shell();
		if (line && line[0])
		{
			free_lexer(&data->lexer);
			free_parser(&data->parser);
			free_redirections(&data->red);
			lexer(data, line);
			// print_lexer(data->lexer);
			error_check(&data->lexer);
			parser(data);
			// print_parser(data->parser);
			redirections(data);
			// print_redirections(data->red);
			// shell_pipex(data);
			executor(data);
		}
		free(line);
		// system("leaks minishell");
	}
}