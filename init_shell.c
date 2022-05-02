#include "includes/minishell.h"

char *init_shell(void)
{
	char *line;

	line = (char *)readline("minishell$> ");
	return (line);
}
