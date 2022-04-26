#include "includes/minishell.h"

char *init_shell(void)
{
	char *line;

	line = readline("minishell$> ");
	return (line);
}
