/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:34:32 by rkoper            #+#    #+#             */
/*   Updated: 2022/09/06 10:33:03 by cdiks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	welcome(void)
{
	printf("%s%s\n", YELLOW, "                                                \
,--.        ,--.   ,--.,--.,--.           ");
	printf("%s%s\n", GREEN, "--.--. ,--,--. ,--,--.,--.  ,--.,---. ,--,--,--.`\
--\',--,--, `--\' ,-|  |`--\'|  |,-.  ,---. ");
	printf("%s%s\n", BLUE, "  .--\'\' ,-.  |\' ,-.  | \\  `\'  /(  .-\' |     \
   |,--.|      \\,--.\' .-. |,--.|     / (  .-\' ");
	printf("%s%s\n", RED, "  |   \\ \'-\'  |\\ \'-\'  |  \\    / .-\'  `)|  | \
 |  ||  ||  ||  ||  |\\ `-\' ||  ||  \\  \\ .-\'  `)");
	printf("%s%s%s\n", YELLOW, "--\'    `--`--\' `--`--\'   `--\'  `----\' `--\
`--`--\'`--\'`--\'\'--\'`--\' `---\' `--\'`--\'`--\'`----\' ", NC);
}

char	*init_shell(void)
{
	char	*line;

	line = (char *)readline("\033[1m\033[32mminishell$>\x1B[0m ");
	if (!line)
	{
		printf("%sExidos!%s\n", RED, NC);
		exit (0);
	}
	add_history(line);
	return (line);
}

void	run_shell(t_data *data)
{
	char	*line;

	welcome();
	handle_signals();
	while (1)
	{
		line = init_shell();
		if (line && line[0])
		{
			free_lexer(&data->lexer);
			free_redirections(&data->red);
			free_parser(&data->parser);
			lexer(data, line);
			error_check(&data->lexer);
			parser(data);
			redirections(data);
			shell_pipex(data);
		}
		free(line);
	}
}
