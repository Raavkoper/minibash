#include "includes/minishell.h"

char *init_shell(void)
{
	char *line;

	line = (char *)readline("minishell$> ");
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
			lexer(data, line);
			// print_lexer(data->lexer);
			parser(data);
			print_parser(data->parser);
			free(line);
		}
	}
}